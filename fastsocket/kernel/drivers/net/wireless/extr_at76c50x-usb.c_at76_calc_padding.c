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
 scalar_t__ AT76_TX_HDRLEN ; 

__attribute__((used)) static inline int at76_calc_padding(int wlen)
{
	/* add the USB TX header */
	wlen += AT76_TX_HDRLEN;

	wlen = wlen % 64;

	if (wlen < 50)
		return 50 - wlen;

	if (wlen >= 61)
		return 64 + 50 - wlen;

	return 0;
}