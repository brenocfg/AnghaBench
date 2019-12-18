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
typedef  int /*<<< orphan*/  uptr ;

/* Variables and functions */
 int /*<<< orphan*/  M68K_MEM_SHIFT ; 
 int /*<<< orphan*/  xmap_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,void const*,int) ; 

void cpu68k_map_set(uptr *map, int start_addr, int end_addr,
    const void *func_or_mh, int is_func)
{
  xmap_set(map, M68K_MEM_SHIFT, start_addr, end_addr, func_or_mh, is_func);
}