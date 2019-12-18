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
struct TYPE_3__ {int fskdcnt; int fsksize; int* fskdata; } ;
typedef  TYPE_1__ IXJ ;

/* Variables and functions */

__attribute__((used)) static void ixj_pad_fsk(IXJ *j, int pad)
{
	int cnt; 

	for (cnt = 0; cnt < pad; cnt++) {
		if(j->fskdcnt < (j->fsksize - 1))
			j->fskdata[j->fskdcnt++] = 0x0000;
	}
	for (cnt = 0; cnt < 720; cnt++) {
		if(j->fskdcnt < (j->fsksize - 1))
			j->fskdata[j->fskdcnt++] = 0x0000;
	}
}