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
typedef  int uptr ;

/* Variables and functions */
 int M68K_MEM_SHIFT ; 
 int* m68k_read16_map ; 
 int* m68k_read8_map ; 
 int* m68k_write16_map ; 
 int* m68k_write8_map ; 
 int* s68k_read16_map ; 
 int* s68k_read8_map ; 
 int* s68k_write16_map ; 
 int* s68k_write8_map ; 

void cpu68k_map_all_ram(int start_addr, int end_addr, void *ptr, int is_sub)
{
  uptr *r8map, *r16map, *w8map, *w16map;
  uptr addr = (uptr)ptr;
  int shift = M68K_MEM_SHIFT;
  int i;

  if (!is_sub) {
    r8map = m68k_read8_map;
    r16map = m68k_read16_map;
    w8map = m68k_write8_map;
    w16map = m68k_write16_map;
  } else {
    r8map = s68k_read8_map;
    r16map = s68k_read16_map;
    w8map = s68k_write8_map;
    w16map = s68k_write16_map;
  }

  addr -= start_addr;
  addr >>= 1;
  for (i = start_addr >> shift; i <= end_addr >> shift; i++)
    r8map[i] = r16map[i] = w8map[i] = w16map[i] = addr;
}