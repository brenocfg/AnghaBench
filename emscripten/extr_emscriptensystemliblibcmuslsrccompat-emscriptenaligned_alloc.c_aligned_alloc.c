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
 int posix_memalign (void**,size_t,size_t) ; 

void *aligned_alloc(size_t alignment, size_t size)
{
  void *ptr;
  int ret = posix_memalign(&ptr, alignment, size);
  return (ret == 0) ? ptr : 0;
}