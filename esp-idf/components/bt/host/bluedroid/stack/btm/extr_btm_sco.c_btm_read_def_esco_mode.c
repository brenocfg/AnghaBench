#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_SCO_TYPE ;
typedef  int /*<<< orphan*/  tBTM_ESCO_PARAMS ;
struct TYPE_3__ {int /*<<< orphan*/  desired_sco_mode; int /*<<< orphan*/  def_esco_parms; } ;
struct TYPE_4__ {TYPE_1__ sco_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_LINK_TYPE_SCO ; 
 TYPE_2__ btm_cb ; 

tBTM_SCO_TYPE btm_read_def_esco_mode (tBTM_ESCO_PARAMS *p_parms)
{
#if (BTM_MAX_SCO_LINKS>0)
    *p_parms = btm_cb.sco_cb.def_esco_parms;
    return btm_cb.sco_cb.desired_sco_mode;
#else
    return BTM_LINK_TYPE_SCO;
#endif
}