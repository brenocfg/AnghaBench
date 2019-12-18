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

/* Variables and functions */
 unsigned long HOST_BITS_PER_LONG ; 
 long double ULONG_MAX ; 

__attribute__((used)) static inline size_t
hash1 (const void *p, unsigned long max, unsigned long logmax)
{
#if HOST_BITS_PER_LONG == 32
  const unsigned long A = 0x9e3779b9u;
#elif HOST_BITS_PER_LONG == 64
  const unsigned long A = 0x9e3779b97f4a7c16ul;
#else
  const unsigned long A
    = (ULONG_MAX + 1.0L) * 0.6180339887498948482045868343656381177203L;
#endif
  const unsigned long shift = HOST_BITS_PER_LONG - logmax;

  return ((A * (unsigned long) p) >> shift) & (max - 1);
}