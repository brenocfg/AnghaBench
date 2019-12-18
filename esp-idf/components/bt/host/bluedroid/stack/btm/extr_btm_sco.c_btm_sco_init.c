#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tSCO_CB ;
struct TYPE_5__ {int /*<<< orphan*/  desired_sco_mode; int /*<<< orphan*/  def_esco_parms; int /*<<< orphan*/  sco_disc_reason; TYPE_1__* sco_db; } ;
struct TYPE_6__ {TYPE_2__ sco_cb; } ;
struct TYPE_4__ {int /*<<< orphan*/  xmit_data_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_DEFAULT_SCO_MODE ; 
 int /*<<< orphan*/  BTM_INVALID_SCO_DISC_REASON ; 
 int BTM_MAX_SCO_LINKS ; 
 int /*<<< orphan*/  QUEUE_SIZE_MAX ; 
 TYPE_3__ btm_cb ; 
 int /*<<< orphan*/  btm_esco_defaults ; 
 int /*<<< orphan*/  fixed_queue_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void btm_sco_init (void)
{
#if 0  /* cleared in btm_init; put back in if called from anywhere else! */
    memset (&btm_cb.sco_cb, 0, sizeof(tSCO_CB));
#endif
#if (BTM_SCO_HCI_INCLUDED == TRUE)
    for (int i = 0; i < BTM_MAX_SCO_LINKS; i++) {
        btm_cb.sco_cb.sco_db[i].xmit_data_q = fixed_queue_new(QUEUE_SIZE_MAX);
    }
#endif
    /* Initialize nonzero defaults */
    btm_cb.sco_cb.sco_disc_reason  = BTM_INVALID_SCO_DISC_REASON;

    btm_cb.sco_cb.def_esco_parms = btm_esco_defaults; /* Initialize with defaults */
    btm_cb.sco_cb.desired_sco_mode = BTM_DEFAULT_SCO_MODE;
}