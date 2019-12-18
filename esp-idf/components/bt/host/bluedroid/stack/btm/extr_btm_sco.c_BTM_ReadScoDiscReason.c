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
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_3__ {int /*<<< orphan*/  sco_disc_reason; } ;
struct TYPE_4__ {TYPE_1__ sco_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_INVALID_SCO_DISC_REASON ; 
 TYPE_2__ btm_cb ; 

UINT16 BTM_ReadScoDiscReason (void)
{
    UINT16 res = btm_cb.sco_cb.sco_disc_reason;
    btm_cb.sco_cb.sco_disc_reason = BTM_INVALID_SCO_DISC_REASON;
    return (res);
}