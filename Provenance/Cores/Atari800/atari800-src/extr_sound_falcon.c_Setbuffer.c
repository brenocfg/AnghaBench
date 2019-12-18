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

/* Variables and functions */
 long* DMActrlptr ; 

void Setbuffer(long bufbeg, long bufsize)
{
	long bufend = bufbeg + bufsize;
	DMActrlptr[1] = (bufbeg >> 16) & 0xff;
	DMActrlptr[2] = (bufbeg >> 8) & 0xff;
	DMActrlptr[3] = bufbeg & 0xff;
	DMActrlptr[7] = (bufend >> 16) & 0xff;
	DMActrlptr[8] = (bufend >> 8) & 0xff;
	DMActrlptr[9] = bufend & 0xff;
}