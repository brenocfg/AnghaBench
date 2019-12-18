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
typedef  int mem_size_t ;

/* Variables and functions */
 void* mem_malloc (int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

void *mem_calloc(mem_size_t count, mem_size_t size)
{
  void *p;

  /* allocate 'count' objects of size 'size' */
  p = mem_malloc(count * size);
  if (p) {
    /* zero the memory */
    memset(p, 0, count * size);
  }
  return p;
}