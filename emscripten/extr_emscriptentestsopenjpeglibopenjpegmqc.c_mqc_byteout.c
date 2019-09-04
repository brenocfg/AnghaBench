#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* bp; int c; int ct; } ;
typedef  TYPE_1__ opj_mqc_t ;

/* Variables and functions */

__attribute__((used)) static void mqc_byteout(opj_mqc_t *mqc) {
	if (*mqc->bp == 0xff) {
		mqc->bp++;
		*mqc->bp = mqc->c >> 20;
		mqc->c &= 0xfffff;
		mqc->ct = 7;
	} else {
		if ((mqc->c & 0x8000000) == 0) {	/* ((mqc->c&0x8000000)==0) CHANGE */
			mqc->bp++;
			*mqc->bp = mqc->c >> 19;
			mqc->c &= 0x7ffff;
			mqc->ct = 8;
		} else {
			(*mqc->bp)++;
			if (*mqc->bp == 0xff) {
				mqc->c &= 0x7ffffff;
				mqc->bp++;
				*mqc->bp = mqc->c >> 20;
				mqc->c &= 0xfffff;
				mqc->ct = 7;
			} else {
				mqc->bp++;
				*mqc->bp = mqc->c >> 19;
				mqc->c &= 0x7ffff;
				mqc->ct = 8;
			}
		}
	}
}