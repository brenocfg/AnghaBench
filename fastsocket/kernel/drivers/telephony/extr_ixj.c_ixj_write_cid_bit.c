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
struct TYPE_3__ {int fskcnt; int fskdcnt; int fsksize; size_t fskz; int /*<<< orphan*/ * fskdata; } ;
typedef  TYPE_1__ IXJ ;

/* Variables and functions */
 int /*<<< orphan*/ *** fsk ; 

__attribute__((used)) static void ixj_write_cid_bit(IXJ *j, int bit)
{
	while (j->fskcnt < 20) {
		if(j->fskdcnt < (j->fsksize - 1))
			j->fskdata[j->fskdcnt++] = fsk[bit][j->fskz][j->fskcnt];

		j->fskcnt += 3;
	}
	j->fskcnt %= 20;

	if (!bit)
		j->fskz++;
	if (j->fskz >= 6)
		j->fskz = 0;

}