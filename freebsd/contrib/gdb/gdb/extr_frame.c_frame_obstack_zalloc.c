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
 int /*<<< orphan*/  frame_cache_obstack ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,unsigned long) ; 
 void* obstack_alloc (int /*<<< orphan*/ *,unsigned long) ; 

void *
frame_obstack_zalloc (unsigned long size)
{
  void *data = obstack_alloc (&frame_cache_obstack, size);
  memset (data, 0, size);
  return data;
}