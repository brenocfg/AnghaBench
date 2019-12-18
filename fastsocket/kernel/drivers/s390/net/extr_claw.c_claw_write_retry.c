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
struct net_device {int dummy; } ;
struct chbk {scalar_t__ claw_state; struct net_device* ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLAW_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ CLAW_STOP ; 
 int /*<<< orphan*/  claw_strt_out_IO (struct net_device*) ; 
 int /*<<< orphan*/  trace ; 

__attribute__((used)) static void
claw_write_retry ( struct chbk *p_ch )
{

        struct net_device  *dev=p_ch->ndev;

	CLAW_DBF_TEXT(4, trace, "w_retry");
        if (p_ch->claw_state == CLAW_STOP) {
        	return;
        }
	claw_strt_out_IO( dev );
	CLAW_DBF_TEXT(4, trace, "rtry_xit");
        return;
}