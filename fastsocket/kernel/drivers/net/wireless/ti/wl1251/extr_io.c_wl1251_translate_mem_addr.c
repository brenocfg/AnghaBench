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
struct wl1251 {int physical_mem_addr; int virtual_mem_addr; } ;

/* Variables and functions */

__attribute__((used)) static int wl1251_translate_mem_addr(struct wl1251 *wl, int addr)
{
	return addr - wl->physical_mem_addr + wl->virtual_mem_addr;
}