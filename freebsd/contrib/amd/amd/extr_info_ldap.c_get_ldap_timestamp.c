#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
typedef  scalar_t__ time_t ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
typedef  int /*<<< orphan*/  filter ;
struct TYPE_6__ {int /*<<< orphan*/  ldap_base; } ;
struct TYPE_5__ {int /*<<< orphan*/ * ldap; } ;
typedef  int /*<<< orphan*/  LDAPMessage ;
typedef  TYPE_1__ ALD ;

/* Variables and functions */
 int AMD_LDAP_RETRIES ; 
 int /*<<< orphan*/  AMD_LDAP_TSATTR ; 
 int /*<<< orphan*/  AMD_LDAP_TSFILTER ; 
 int ENOENT ; 
 int /*<<< orphan*/  LDAP_SCOPE_SUBTREE ; 
 int LDAP_SUCCESS ; 
 int LDAP_TIMEOUT ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  XLOG_USER ; 
 scalar_t__ amu_ldap_rebind (TYPE_1__*) ; 
 int /*<<< orphan*/  amu_ldap_unbind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlog (char*,...) ; 
 TYPE_2__ gopt ; 
 int ldap_count_entries (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ldap_count_values (char**) ; 
 char* ldap_err2string (int) ; 
 int /*<<< orphan*/ * ldap_first_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char** ldap_get_values (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldap_msgfree (int /*<<< orphan*/ *) ; 
 int ldap_search_st (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ldap_value_free (char**) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ strtol (char*,char**,int) ; 
 int /*<<< orphan*/  xsnprintf (char*,int,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
get_ldap_timestamp(ALD *a, char *map, time_t *ts)
{
  struct timeval tv;
  char **vals, *end;
  char filter[MAXPATHLEN];
  int i, err = 0, nentries = 0;
  LDAPMessage *res = NULL, *entry;

  dlog("-> get_ldap_timestamp: map <%s>\n", map);

  tv.tv_sec = 3;
  tv.tv_usec = 0;
  xsnprintf(filter, sizeof(filter), AMD_LDAP_TSFILTER, map);
  dlog("Getting timestamp for map %s\n", map);
  dlog("Filter is: %s\n", filter);
  dlog("Base is: %s\n", gopt.ldap_base);
  for (i = 0; i < AMD_LDAP_RETRIES; i++) {
    err = ldap_search_st(a->ldap,
			 gopt.ldap_base,
			 LDAP_SCOPE_SUBTREE,
			 filter,
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
    plog(XLOG_USER, "Timestamp LDAP search attempt %d failed: %s\n",
	 i + 1, ldap_err2string(err));
    if (err != LDAP_TIMEOUT) {
      dlog("get_ldap_timestamp: unbinding...\n");
      amu_ldap_unbind(a->ldap);
      a->ldap = NULL;
      if (amu_ldap_rebind(a))
        return (ENOENT);
    }
    dlog("Timestamp search failed, trying again...\n");
  }

  if (err != LDAP_SUCCESS) {
    *ts = 0;
    plog(XLOG_USER, "LDAP timestamp search failed: %s\n",
	 ldap_err2string(err));
    if (res)
      ldap_msgfree(res);
    return (ENOENT);
  }

  nentries = ldap_count_entries(a->ldap, res);
  if (nentries == 0) {
    plog(XLOG_USER, "No timestamp entry for map %s\n", map);
    *ts = 0;
    ldap_msgfree(res);
    return (ENOENT);
  }

  entry = ldap_first_entry(a->ldap, res);
  vals = ldap_get_values(a->ldap, entry, AMD_LDAP_TSATTR);
  if (ldap_count_values(vals) == 0) {
    plog(XLOG_USER, "Missing timestamp value for map %s\n", map);
    *ts = 0;
    ldap_value_free(vals);
    ldap_msgfree(res);
    return (ENOENT);
  }
  dlog("TS value is:%s:\n", vals[0]);

  if (vals[0]) {
    *ts = (time_t) strtol(vals[0], &end, 10);
    if (end == vals[0]) {
      plog(XLOG_USER, "Unable to decode ldap timestamp %s for map %s\n",
	   vals[0], map);
      err = ENOENT;
    }
    if (!*ts > 0) {
      plog(XLOG_USER, "Nonpositive timestamp %ld for map %s\n",
	   (u_long) *ts, map);
      err = ENOENT;
    }
  } else {
    plog(XLOG_USER, "Empty timestamp value for map %s\n", map);
    *ts = 0;
    err = ENOENT;
  }

  ldap_value_free(vals);
  ldap_msgfree(res);
  dlog("The timestamp for %s is %ld (err=%d)\n", map, (u_long) *ts, err);
  return (err);
}