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
typedef  int _uw ;

/* Variables and functions */

__attribute__((used)) static inline _uw
selfrel_offset31 (const _uw *p)
{
  _uw offset;

  offset = *p;
  /* Sign extend to 32 bits.  */
  if (offset & (1 << 30))
    offset |= 1u << 31;

  return offset + (_uw) p;
}