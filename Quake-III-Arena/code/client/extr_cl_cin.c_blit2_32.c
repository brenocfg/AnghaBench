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
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */

__attribute__((used)) static void blit2_32( byte *src, byte *dst, int spl  )
{
	double *dsrc, *ddst;
	int dspl;

	dsrc = (double *)src;
	ddst = (double *)dst;
	dspl = spl>>3;

	ddst[0] = dsrc[0];
	ddst[dspl] = dsrc[1];
}