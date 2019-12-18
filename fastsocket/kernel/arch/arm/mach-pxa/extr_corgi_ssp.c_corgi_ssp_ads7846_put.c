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
typedef  int /*<<< orphan*/  ulong ;

/* Variables and functions */
 int /*<<< orphan*/  corgi_ssp_dev ; 
 int /*<<< orphan*/  ssp_write_word (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void corgi_ssp_ads7846_put(ulong data)
{
	ssp_write_word(&corgi_ssp_dev,data);
}