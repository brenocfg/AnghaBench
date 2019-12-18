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
typedef  int /*<<< orphan*/  mem_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  mem_free (void*) ; 
 void* mem_malloc (int /*<<< orphan*/ ) ; 
 void* mem_realloc (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 

void *
mem_reallocm(void *rmem, mem_size_t newsize)
{
  void *nmem;
  nmem = mem_malloc(newsize);
  if (nmem == NULL) {
    return mem_realloc(rmem, newsize);
  }
  memcpy(nmem, rmem, newsize);
  mem_free(rmem);
  return nmem;
}