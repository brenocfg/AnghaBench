#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct net_device {int /*<<< orphan*/  trans_start; scalar_t__ ml_priv; } ;
struct claw_privbk {struct ccwbk* p_write_active_first; struct chbk* channel; } ;
struct chbk {scalar_t__ claw_state; int /*<<< orphan*/  cdev; int /*<<< orphan*/  IO_active; } ;
struct ccwbk {int /*<<< orphan*/  write; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLAW_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ CLAW_STOP ; 
 size_t WRITE ; 
 int /*<<< orphan*/  ccw_check_return_code (int /*<<< orphan*/ ,int) ; 
 int ccw_device_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  trace ; 

__attribute__((used)) static void
claw_strt_out_IO( struct net_device *dev )
{
        int             	rc = 0;
        unsigned long   	parm;
        struct claw_privbk 	*privptr;
        struct chbk     	*p_ch;
        struct ccwbk   	*p_first_ccw;

	if (!dev) {
		return;
	}
	privptr = (struct claw_privbk *)dev->ml_priv;
        p_ch=&privptr->channel[WRITE];

	CLAW_DBF_TEXT(4, trace, "strt_io");
        p_first_ccw=privptr->p_write_active_first;

        if (p_ch->claw_state == CLAW_STOP)
                return;
        if (p_first_ccw == NULL) {
                return;
        }
        if (test_and_set_bit(0, (void *)&p_ch->IO_active) == 0) {
                parm = (unsigned long) p_ch;
		CLAW_DBF_TEXT(2, trace, "StWrtIO");
		rc = ccw_device_start(p_ch->cdev, &p_first_ccw->write, parm,
				      0xff, 0);
                if (rc != 0) {
                        ccw_check_return_code(p_ch->cdev, rc);
                }
        }
        dev->trans_start = jiffies;
        return;
}