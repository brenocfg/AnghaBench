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
struct pvr2_hdw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pvr2_hdw_get_desc (struct pvr2_hdw*) ; 
 int pvr2_hdw_state_report (struct pvr2_hdw*,char*,unsigned int) ; 
 int scnprintf (char*,unsigned int,char*,...) ; 

int pvr2_debugifc_print_info(struct pvr2_hdw *hdw,char *buf,unsigned int acnt)
{
	int bcnt = 0;
	int ccnt;
	ccnt = scnprintf(buf, acnt, "Driver hardware description: %s\n",
			 pvr2_hdw_get_desc(hdw));
	bcnt += ccnt; acnt -= ccnt; buf += ccnt;
	ccnt = scnprintf(buf,acnt,"Driver state info:\n");
	bcnt += ccnt; acnt -= ccnt; buf += ccnt;
	ccnt = pvr2_hdw_state_report(hdw,buf,acnt);
	bcnt += ccnt; acnt -= ccnt; buf += ccnt;

	return bcnt;
}