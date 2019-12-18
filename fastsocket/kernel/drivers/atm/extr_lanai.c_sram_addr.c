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
struct lanai_dev {scalar_t__ base; } ;
typedef  scalar_t__ bus_addr_t ;

/* Variables and functions */
 scalar_t__ SRAM_START ; 

__attribute__((used)) static inline bus_addr_t sram_addr(const struct lanai_dev *lanai, int offset)
{
	return lanai->base + SRAM_START + offset;
}