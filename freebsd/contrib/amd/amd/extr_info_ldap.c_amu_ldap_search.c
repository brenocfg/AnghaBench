#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_8__ {TYPE_1__* cfm; scalar_t__ map_data; } ;
typedef  TYPE_2__ mnt_map ;
typedef  int /*<<< orphan*/  filter ;
struct TYPE_10__ {int /*<<< orphan*/  ldap_base; } ;
struct TYPE_9__ {int /*<<< orphan*/ * ldap; } ;
struct TYPE_7__ {int cfm_flags; } ;
typedef  int /*<<< orphan*/  LDAPMessage ;
typedef  TYPE_3__ ALD ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_LDAP_ATTR ; 
 int /*<<< orphan*/  AMD_LDAP_FILTER ; 
 int AMD_LDAP_RETRIES ; 
 int CFM_SUN_MAP_SYNTAX ; 
 int EIO ; 
 int ENOENT ; 
#define  LDAP_NO_SUCH_OBJECT 129 
 int /*<<< orphan*/  LDAP_SCOPE_SUBTREE ; 
#define  LDAP_SUCCESS 128 
 int LDAP_TIMEOUT ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  XLOG_USER ; 
 scalar_t__ amu_ldap_rebind (TYPE_3__*) ; 
 int /*<<< orphan*/  amu_ldap_unbind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlog (char*,...) ; 
 TYPE_4__ gopt ; 
 int ldap_count_entries (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ldap_count_values (char**) ; 
 int /*<<< orphan*/  ldap_err2string (int) ; 
 int /*<<< orphan*/ * ldap_first_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char** ldap_get_values (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldap_msgfree (int /*<<< orphan*/ *) ; 
 int ldap_search_st (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ldap_value_free (char**) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,...) ; 
 char* sun_entry2amd (char*,char*) ; 
 int /*<<< orphan*/  xsnprintf (char*,int,int /*<<< orphan*/ ,char*,char*) ; 
 char* xstrdup (char*) ; 

int
amu_ldap_search(mnt_map *m, char *map, char *key, char **pval, time_t *ts)
{
  char **vals, filter[MAXPATHLEN], filter2[2 * MAXPATHLEN];
  char *f1, *f2;
  struct timeval tv;
  int i, err = 0, nvals = 0, nentries = 0;
  LDAPMessage *entry, *res = NULL;
  ALD *a = (ALD *) (m->map_data);

  dlog("-> amu_ldap_search: map <%s>, key <%s>\n", map, key);

  tv.tv_sec = 2;
  tv.tv_usec = 0;
  if (a == NULL) {
    plog(XLOG_USER, "LDAP panic: no map data\n");
    return (EIO);
  }
  if (amu_ldap_rebind(a))	/* Check that's the handle is still valid */
    return (ENOENT);

  xsnprintf(filter, sizeof(filter), AMD_LDAP_FILTER, map, key);
  /* "*" is special to ldap_search(); run through the filter escaping it. */
  f1 = filter; f2 = filter2;
  while (*f1) {
    if (*f1 == '*') {
      *f2++ = '\\'; *f2++ = '2'; *f2++ = 'a';
      f1++;
    } else {
      *f2++ = *f1++;
    }
  }
  *f2 = '\0';
  dlog("Search with filter: <%s>\n", filter2);
  for (i = 0; i < AMD_LDAP_RETRIES; i++) {
    err = ldap_search_st(a->ldap,
			 gopt.ldap_base,
			 LDAP_SCOPE_SUBTREE,
			 filter2,
			 0,
			 0,
			 &tv,
			 &res);
    if (err == LDAP_SUCCESS)
      break;
    if (res) {
      ldap_msgfree(res);
      res = NULL;
    }
    plog(XLOG_USER, "LDAP search attempt %d failed: %s\n",
        i + 1, ldap_err2string(err));
    if (err != LDAP_TIMEOUT) {
      dlog("amu_ldap_search: unbinding...\n");
      amu_ldap_unbind(a->ldap);
      a->ldap = NULL;
      if (amu_ldap_rebind(a))
        return (ENOENT);
    }
  }

  switch (err) {
  case LDAP_SUCCESS:
    break;
  case LDAP_NO_SUCH_OBJECT:
    dlog("No object\n");
    if (res)
      ldap_msgfree(res);
    return (ENOENT);
  default:
    plog(XLOG_USER, "LDAP search failed: %s\n",
	 ldap_err2string(err));
    if (res)
      ldap_msgfree(res);
    return (EIO);
  }

  nentries = ldap_count_entries(a->ldap, res);
  dlog("Search found %d entries\n", nentries);
  if (nentries == 0) {
    ldap_msgfree(res);
    return (ENOENT);
  }
  entry = ldap_first_entry(a->ldap, res);
  vals = ldap_get_values(a->ldap, entry, AMD_LDAP_ATTR);
  nvals = ldap_count_values(vals);
  if (nvals == 0) {
    plog(XLOG_USER, "Missing value for %s in map %s\n", key, map);
    ldap_value_free(vals);
    ldap_msgfree(res);
    return (EIO);
  }
  dlog("Map %s, %s => %s\n", map, key, vals[0]);
  if (vals[0]) {
    if (m->cfm && (m->cfm->cfm_flags & CFM_SUN_MAP_SYNTAX))
      *pval = sun_entry2amd(key, vals[0]);
    else
      *pval = xstrdup(vals[0]);
    err = 0;
  } else {
    plog(XLOG_USER, "Empty value for %s in map %s\n", key, map);
    err = ENOENT;
  }
  ldap_msgfree(res);
  ldap_value_free(vals);

  return (err);
}