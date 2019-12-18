#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_7__ {TYPE_1__* cfm; } ;
typedef  TYPE_2__ mnt_map ;
typedef  int /*<<< orphan*/  hes_key ;
struct TYPE_9__ {int /*<<< orphan*/  options; } ;
struct TYPE_8__ {int hesiod_base; } ;
struct TYPE_6__ {int cfm_flags; } ;

/* Variables and functions */
 int CFM_SUN_MAP_SYNTAX ; 
 int /*<<< orphan*/  D_INFO ; 
 int EINVAL ; 
 int EIO ; 
 int ENOENT ; 
 int ETIMEDOUT ; 
#define  HES_ER_CONFIG 130 
#define  HES_ER_NET 129 
#define  HES_ER_NOTFOUND 128 
 int HES_PREFLEN ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  RES_DEBUG ; 
 int /*<<< orphan*/  XFREE (char*) ; 
 TYPE_5__ _res ; 
 scalar_t__ amuDebug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlog (char*,...) ; 
 int errno ; 
 TYPE_4__ gopt ; 
 long hes_error () ; 
 char** hes_resolve (char*,int) ; 
 int /*<<< orphan*/  hesiod_context ; 
 char** hesiod_resolve (int /*<<< orphan*/ ,char*,int) ; 
 char* sun_entry2amd (char*,char*) ; 
 int /*<<< orphan*/  xsnprintf (char*,int,char*,char*,char*) ; 

int
hesiod_search(mnt_map *m, char *map, char *key, char **pval, time_t *tp)
{
  char hes_key[MAXPATHLEN];
  char **rvec;
#ifndef HAVE_HESIOD_INIT
  int error;
#endif /* not HAVE_HESIOD_INIT */

  dlog("hesiod_search(m=%lx, map=%s, key=%s, pval=%lx tp=%lx)",
       (unsigned long) m, map, key, (unsigned long) pval, (unsigned long) tp);

  if (key[0] == '.')
    return ENOENT;

  xsnprintf(hes_key, sizeof(hes_key), "%s.%s", key, map + HES_PREFLEN);

  /*
   * Call the resolver
   */
  dlog("Hesiod base is: %s\n", gopt.hesiod_base);
  dlog("hesiod_search: hes_resolve(%s, %s)", hes_key, gopt.hesiod_base);
  if (amuDebug(D_INFO))
    _res.options |= RES_DEBUG;

#ifdef HAVE_HESIOD_INIT
  /* new style hesiod */
  rvec = hesiod_resolve(hesiod_context, hes_key, gopt.hesiod_base);
#else /* not HAVE_HESIOD_INIT */
  rvec = hes_resolve(hes_key, gopt.hesiod_base);
#endif /* not HAVE_HESIOD_INIT */

  /*
   * If a reply was forthcoming then return
   * it (and free subsequent replies)
   */
  if (rvec && *rvec) {
    if (m->cfm && (m->cfm->cfm_flags & CFM_SUN_MAP_SYNTAX)) {
      *pval = sun_entry2amd(key, *rvec);
      XFREE(*rvec);
    } else
      *pval = *rvec;
    while (*++rvec)
      XFREE(*rvec);
    return 0;
  }

#ifdef HAVE_HESIOD_INIT
  /* new style hesiod */
  return errno;
#else /* not HAVE_HESIOD_INIT */
  /*
   * Otherwise reflect the hesiod error into a Un*x error
   */
  dlog("hesiod_search: Error: %d", hes_error());
  switch (hes_error()) {
  case HES_ER_NOTFOUND:
    error = ENOENT;
    break;
  case HES_ER_CONFIG:
    error = EIO;
    break;
  case HES_ER_NET:
    error = ETIMEDOUT;
    break;
  default:
    error = EINVAL;
    break;
  }
  dlog("hesiod_search: Returning: %d", error);
  return error;
#endif /* not HAVE_HESIOD_INIT */
}