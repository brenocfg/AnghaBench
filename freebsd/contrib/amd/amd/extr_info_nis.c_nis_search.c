#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct TYPE_7__ {TYPE_1__* cfm; } ;
typedef  TYPE_2__ mnt_map ;
typedef  int /*<<< orphan*/  YP_ORDER_OUTORDER_TYPE ;
struct TYPE_8__ {int /*<<< orphan*/  nis_domain; scalar_t__ am_timeo; } ;
struct TYPE_6__ {int cfm_flags; } ;

/* Variables and functions */
 int CFM_SUN_MAP_SYNTAX ; 
 int EIO ; 
 int ENOENT ; 
 int /*<<< orphan*/  XFREE (char*) ; 
 int /*<<< orphan*/  XLOG_ERROR ; 
#define  YPERR_KEY 128 
 int determine_nis_domain () ; 
 TYPE_5__ gopt ; 
 int has_yp_order ; 
 int /*<<< orphan*/  nis_isup (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* sun_entry2amd (char*,char*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int yp_match (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char**,int*) ; 
 int /*<<< orphan*/  yp_order (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yperr_string (int) ; 

int
nis_search(mnt_map *m, char *map, char *key, char **pval, time_t *tp)
{
  int outlen;
  int res;
  YP_ORDER_OUTORDER_TYPE order;

  /*
   * Make sure domain initialized
   */
  if (!gopt.nis_domain) {
    int error = determine_nis_domain();
    if (error)
      return error;
  }


  switch (has_yp_order) {
  case 1:
    /*
     * NIS server with yp_order
     * Check if map has changed
     */
    if (yp_order(gopt.nis_domain, map, &order))
      return EIO;
    if ((time_t) order > *tp) {
      *tp = (time_t) order;
      return -1;
    }
    break;

  case 0:
    /*
     * NIS+ server without yp_order
     * Check if timeout has expired to invalidate the cache
     */
    order = time(NULL);
    if ((time_t)order - *tp > gopt.am_timeo) {
      *tp = (time_t)order;
      return(-1);
    }
    break;

  default:
    /*
     * server was down
     */
     if (nis_isup(m, map))
       return -1;
     return EIO;
  }

  /*
   * Lookup key
   */
  res = yp_match(gopt.nis_domain, map, key, strlen(key), pval, &outlen);
  if (m->cfm && (m->cfm->cfm_flags & CFM_SUN_MAP_SYNTAX) && res == 0) {
    char *oldval = *pval;
    *pval = sun_entry2amd(key, oldval);
    /* We always need to free the output of the yp_match call. */
    XFREE(oldval);
    if (*pval == NULL)
      return -1;		/* sun2amd parser error */
  }

  /*
   * Do something interesting with the return code
   */
  switch (res) {
  case 0:
    return 0;

  case YPERR_KEY:
    return ENOENT;

  default:
    plog(XLOG_ERROR, "nis_search: %s: %s", map, yperr_string(res));
    return EIO;
  }
}