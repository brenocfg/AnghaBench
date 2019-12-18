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
 int /*<<< orphan*/  BITS_PER_CPPCHAR_T ; 
 int CHAR_BIT ; 
 size_t MIN (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline size_t
width_to_mask (size_t width)
{
  width = MIN (width, BITS_PER_CPPCHAR_T);
  if (width >= CHAR_BIT * sizeof (size_t))
    return ~(size_t) 0;
  else
    return ((size_t) 1 << width) - 1;
}