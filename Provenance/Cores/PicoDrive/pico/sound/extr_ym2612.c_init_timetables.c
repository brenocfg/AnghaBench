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
typedef  scalar_t__ UINT8 ;
struct TYPE_4__ {double freqbase; int /*<<< orphan*/ ** dt_tab; } ;
struct TYPE_5__ {TYPE_1__ ST; } ;
struct TYPE_6__ {TYPE_2__ OPN; } ;
typedef  int /*<<< orphan*/  INT32 ;

/* Variables and functions */
 int FREQ_SH ; 
 double SIN_LEN ; 
 TYPE_3__ ym2612 ; 

__attribute__((used)) static void init_timetables(const UINT8 *dttable)
{
	int i,d;
	double rate;

	/* DeTune table */
	for (d = 0;d <= 3;d++){
		for (i = 0;i <= 31;i++){
			rate = ((double)dttable[d*32 + i]) * SIN_LEN  * ym2612.OPN.ST.freqbase  * (1<<FREQ_SH) / ((double)(1<<20));
			ym2612.OPN.ST.dt_tab[d][i]   = (INT32) rate;
			ym2612.OPN.ST.dt_tab[d+4][i] = -ym2612.OPN.ST.dt_tab[d][i];
		}
	}
}