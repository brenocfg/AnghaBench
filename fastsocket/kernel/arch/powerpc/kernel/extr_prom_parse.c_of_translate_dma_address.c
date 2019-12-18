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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __of_translate_address (struct device_node*,int /*<<< orphan*/  const*,char*) ; 

u64 of_translate_dma_address(struct device_node *dev, const u32 *in_addr)
{
	return __of_translate_address(dev, in_addr, "dma-ranges");
}