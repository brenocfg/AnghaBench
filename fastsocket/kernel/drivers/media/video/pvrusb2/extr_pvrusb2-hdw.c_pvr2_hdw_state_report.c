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
struct pvr2_hdw {int /*<<< orphan*/  big_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_GIVE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCK_TAKE (int /*<<< orphan*/ ) ; 
 unsigned int pvr2_hdw_report_clients (struct pvr2_hdw*,char*,unsigned int) ; 
 unsigned int pvr2_hdw_report_unlocked (struct pvr2_hdw*,unsigned int,char*,unsigned int) ; 

unsigned int pvr2_hdw_state_report(struct pvr2_hdw *hdw,
				   char *buf,unsigned int acnt)
{
	unsigned int bcnt,ccnt,idx;
	bcnt = 0;
	LOCK_TAKE(hdw->big_lock);
	for (idx = 0; ; idx++) {
		ccnt = pvr2_hdw_report_unlocked(hdw,idx,buf,acnt);
		if (!ccnt) break;
		bcnt += ccnt; acnt -= ccnt; buf += ccnt;
		if (!acnt) break;
		buf[0] = '\n'; ccnt = 1;
		bcnt += ccnt; acnt -= ccnt; buf += ccnt;
	}
	ccnt = pvr2_hdw_report_clients(hdw, buf, acnt);
	bcnt += ccnt; acnt -= ccnt; buf += ccnt;
	LOCK_GIVE(hdw->big_lock);
	return bcnt;
}