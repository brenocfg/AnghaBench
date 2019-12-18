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
typedef  int file_ptr ;

/* Variables and functions */

__attribute__((used)) static inline file_ptr
align_file_position (file_ptr off, int align)
{
  return (off + align - 1) & ~(align - 1);
}