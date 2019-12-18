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
 int EL_ANOMALY ; 
 int EL_STATUS ; 
 int MAP_FLAG ; 
 int /*<<< orphan*/  elprintf (int,char*,int volatile,...) ; 

__attribute__((used)) static void xmap_set(uptr *map, int shift, int start_addr, int end_addr,
    const void *func_or_mh, int is_func)
{
#ifdef __clang__
  // workaround bug (segfault) in 
  // Apple LLVM version 4.2 (clang-425.0.27) (based on LLVM 3.2svn)
  volatile 
#endif
  uptr addr = (uptr)func_or_mh;
  int mask = (1 << shift) - 1;
  int i;

  if ((start_addr & mask) != 0 || (end_addr & mask) != mask) {
    elprintf(EL_STATUS|EL_ANOMALY, "xmap_set: tried to map bad range: %06x-%06x",
      start_addr, end_addr);
    return;
  }

  if (addr & 1) {
    elprintf(EL_STATUS|EL_ANOMALY, "xmap_set: ptr is not aligned: %08lx", addr);
    return;
  }

  if (!is_func)
    addr -= start_addr;

  for (i = start_addr >> shift; i <= end_addr >> shift; i++) {
    map[i] = addr >> 1;
    if (is_func)
      map[i] |= MAP_FLAG;
  }
}