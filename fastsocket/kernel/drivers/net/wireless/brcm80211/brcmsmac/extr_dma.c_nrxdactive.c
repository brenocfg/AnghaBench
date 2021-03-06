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
typedef  scalar_t__ uint ;
struct dma_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ rxd (struct dma_info*,scalar_t__) ; 

__attribute__((used)) static uint nrxdactive(struct dma_info *di, uint h, uint t)
{
	return rxd(di, t-h);
}