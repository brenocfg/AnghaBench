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
 int volatile MAP_FLAG ; 
 int* m68k_read16_map ; 
 int* m68k_read8_map ; 
 scalar_t__ m68k_unmapped_read16 ; 
 scalar_t__ m68k_unmapped_read8 ; 
 scalar_t__ m68k_unmapped_write16 ; 
 scalar_t__ m68k_unmapped_write8 ; 
 int* m68k_write16_map ; 
 int* m68k_write8_map ; 

void m68k_map_unmap(int start_addr, int end_addr)
{
#ifdef __clang__
  // workaround bug (segfault) in 
  // Apple LLVM version 4.2 (clang-425.0.27) (based on LLVM 3.2svn)
  volatile 
#endif
  uptr addr;
  int shift = M68K_MEM_SHIFT;
  int i;

  addr = (uptr)m68k_unmapped_read8;
  for (i = start_addr >> shift; i <= end_addr >> shift; i++)
    m68k_read8_map[i] = (addr >> 1) | MAP_FLAG;

  addr = (uptr)m68k_unmapped_read16;
  for (i = start_addr >> shift; i <= end_addr >> shift; i++)
    m68k_read16_map[i] = (addr >> 1) | MAP_FLAG;

  addr = (uptr)m68k_unmapped_write8;
  for (i = start_addr >> shift; i <= end_addr >> shift; i++)
    m68k_write8_map[i] = (addr >> 1) | MAP_FLAG;

  addr = (uptr)m68k_unmapped_write16;
  for (i = start_addr >> shift; i <= end_addr >> shift; i++)
    m68k_write16_map[i] = (addr >> 1) | MAP_FLAG;
}