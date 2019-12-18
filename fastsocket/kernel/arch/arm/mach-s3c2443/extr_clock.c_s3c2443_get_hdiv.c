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
 unsigned long S3C2443_CLKDIV0_HCLKDIV_MASK ; 

__attribute__((used)) static inline unsigned long s3c2443_get_hdiv(unsigned long clkcon0)
{
	clkcon0 &= S3C2443_CLKDIV0_HCLKDIV_MASK;

	return clkcon0 + 1;
}