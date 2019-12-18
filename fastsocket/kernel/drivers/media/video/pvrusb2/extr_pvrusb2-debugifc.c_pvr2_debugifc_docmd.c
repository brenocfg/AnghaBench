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
 int pvr2_debugifc_do1cmd (struct pvr2_hdw*,char const*,unsigned int) ; 

int pvr2_debugifc_docmd(struct pvr2_hdw *hdw,const char *buf,
			unsigned int count)
{
	unsigned int bcnt = 0;
	int ret;

	while (count) {
		for (bcnt = 0; bcnt < count; bcnt++) {
			if (buf[bcnt] == '\n') break;
		}

		ret = pvr2_debugifc_do1cmd(hdw,buf,bcnt);
		if (ret < 0) return ret;
		if (bcnt < count) bcnt++;
		buf += bcnt;
		count -= bcnt;
	}

	return 0;
}