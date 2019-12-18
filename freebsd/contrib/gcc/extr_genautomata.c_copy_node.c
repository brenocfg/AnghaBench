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
 void* create_node (size_t) ; 
 int /*<<< orphan*/  memcpy (void* const,void const*,size_t) ; 

__attribute__((used)) static void *
copy_node (const void *from, size_t size)
{
  void *const result = create_node (size);
  memcpy (result, from, size);
  return result;
}