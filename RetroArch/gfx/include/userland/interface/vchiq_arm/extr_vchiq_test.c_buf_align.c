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

__attribute__((used)) static char *buf_align(char *buf, int align_size, int align)
{
   char *aligned = buf - ((intptr_t)buf & (align_size - 1)) + align;
   if (aligned < buf)
      aligned += align_size;
   return aligned;
}