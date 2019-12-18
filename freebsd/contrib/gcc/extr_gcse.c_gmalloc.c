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
 size_t bytes_used ; 
 void* xmalloc (size_t) ; 

__attribute__((used)) static void *
gmalloc (size_t size)
{
  bytes_used += size;
  return xmalloc (size);
}