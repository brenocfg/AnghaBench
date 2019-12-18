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
typedef  unsigned long u32 ;

/* Variables and functions */
 int /*<<< orphan*/  corgi_ssp_dev ; 
 int /*<<< orphan*/  ssp_read_word (int /*<<< orphan*/ *,unsigned long*) ; 

unsigned long corgi_ssp_ads7846_get(void)
{
	u32 ret = 0;
	ssp_read_word(&corgi_ssp_dev, &ret);
	return ret;
}