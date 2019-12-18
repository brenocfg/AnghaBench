#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  mnt_map ;
typedef  scalar_t__ YP_ORDER_OUTORDER_TYPE ;
struct TYPE_2__ {int /*<<< orphan*/  nis_domain; } ;

/* Variables and functions */
 int ENOENT ; 
#define  YPERR_YPERR 128 
 int determine_nis_domain () ; 
 int /*<<< orphan*/  dlog (char*,char*,int /*<<< orphan*/ ,...) ; 
 TYPE_1__ gopt ; 
 int has_yp_order ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yp_master (int /*<<< orphan*/ ,char*,char**) ; 
 int yp_order (int /*<<< orphan*/ ,char*,scalar_t__*) ; 

int
nis_init(mnt_map *m, char *map, time_t *tp)
{
  YP_ORDER_OUTORDER_TYPE order;
  int yp_order_result;
  char *master;

  if (!gopt.nis_domain) {
    int error = determine_nis_domain();
    if (error)
      return error;
  }

  /*
   * To see if the map exists, try to find
   * a master for it.
   */
  yp_order_result = yp_order(gopt.nis_domain, map, &order);
  switch (yp_order_result) {
  case 0:
    /* NIS server found */
    has_yp_order = 1;
    *tp = (time_t) order;
    dlog("NIS master for %s@%s has order %lu", map, gopt.nis_domain, (unsigned long) order);
    break;
  case YPERR_YPERR:
    /* NIS+ server found ! */
    has_yp_order = 0;
    /* try yp_master() instead */
    if (yp_master(gopt.nis_domain, map, &master)) {
      return ENOENT;
    } else {
      dlog("NIS master for %s@%s is a NIS+ server", map, gopt.nis_domain);
      /* Use fake timestamps */
      *tp = time(NULL);
    }
    break;
  default:
    /* server is down */
    has_yp_order = -1;
    return ENOENT;
  }
  return 0;
}