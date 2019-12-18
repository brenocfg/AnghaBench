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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int,int,int) ; 

__attribute__((used)) static void r600_hdmi_calc_cts(uint32_t clock, int *CTS, int N, int freq)
{
	if (*CTS == 0)
		*CTS = clock * N / (128 * freq) * 1000;
	DRM_DEBUG("Using ACR timing N=%d CTS=%d for frequency %d\n",
		  N, *CTS, freq);
}