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
typedef  int u64 ;
struct hdsp {int dds_value; } ;

/* Variables and functions */
 int DDS_NUMERATOR ; 
 int /*<<< orphan*/  HDSP_freqReg ; 
 int div_u64 (int,int) ; 
 int /*<<< orphan*/  hdsp_write (struct hdsp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_BUG_ON (int) ; 

__attribute__((used)) static void hdsp_set_dds_value(struct hdsp *hdsp, int rate)
{
	u64 n;

	if (rate >= 112000)
		rate /= 4;
	else if (rate >= 56000)
		rate /= 2;

	n = DDS_NUMERATOR;
	n = div_u64(n, rate);
	/* n should be less than 2^32 for being written to FREQ register */
	snd_BUG_ON(n >> 32);
	/* HDSP_freqReg and HDSP_resetPointer are the same, so keep the DDS
	   value to write it after a reset */
	hdsp->dds_value = n;
	hdsp_write(hdsp, HDSP_freqReg, hdsp->dds_value);
}