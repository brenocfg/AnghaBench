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
typedef  int /*<<< orphan*/  tBTM_SCO_IND_CBACK ;
struct TYPE_3__ {int /*<<< orphan*/ * app_sco_ind_cb; } ;
struct TYPE_4__ {TYPE_1__ sco_cb; } ;

/* Variables and functions */
 TYPE_2__ btm_cb ; 

void btm_set_sco_ind_cback( tBTM_SCO_IND_CBACK *sco_ind_cb )
{
    btm_cb.sco_cb.app_sco_ind_cb = sco_ind_cb;
}