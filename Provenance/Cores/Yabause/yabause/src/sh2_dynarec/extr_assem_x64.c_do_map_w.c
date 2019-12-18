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
 scalar_t__ can_direct_write (int) ; 
 int /*<<< orphan*/  emit_mov (int,int) ; 
 int /*<<< orphan*/  emit_movmem_indexedx8_64 (int,int,int) ; 
 int /*<<< orphan*/  emit_movq (int,int) ; 
 int /*<<< orphan*/  emit_shlimm64 (int,int,int) ; 
 int /*<<< orphan*/  emit_shrimm (int,int,int) ; 
 int /*<<< orphan*/  emit_xorimm (int,int,int) ; 
 scalar_t__ memory_map ; 

int do_map_w(int s,int ar,int map,int cache,int x,int c,u32 addr)
{
  if(c) {
    if(can_direct_write(addr)) {
      emit_movq((int)(memory_map+(addr>>12)),map);
    }
    else
      return -1; // No mapping
  }
  else {
    if(s!=map) emit_mov(s,map);
    //if(s!=ar) emit_mov(s,ar);
    emit_shrimm(map,12,map);
    // Schedule this while we wait on the load
    if(x) emit_xorimm(s,x,ar);
    emit_movmem_indexedx8_64((int)memory_map,map,map);
  }
  emit_shlimm64(map,2,map);
  return map;
}