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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  dynarec_local ; 
 int /*<<< orphan*/  emit_movimm (int,int) ; 
 scalar_t__ memory_map ; 

generate_map_const(u32 addr,int reg) {
  //printf("generate_map_const(%x,%s)\n",addr,regname[reg]);
  emit_movimm((addr>>12)+(((u32)memory_map-(u32)&dynarec_local)>>2),reg);
}