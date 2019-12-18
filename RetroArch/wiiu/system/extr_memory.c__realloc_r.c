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
struct _reent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _free_r (struct _reent*,void*) ; 
 void* _malloc_r (struct _reent*,size_t) ; 
 size_t _malloc_usable_size_r (struct _reent*,void*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 

void * _realloc_r(struct _reent *r, void *ptr, size_t size)
{
   void *realloc_ptr = NULL;
   if (!ptr)
      return _malloc_r(r, size);

   if (_malloc_usable_size_r(r, ptr) >= size)
      return ptr;

   realloc_ptr = _malloc_r(r, size);

   if(!realloc_ptr)
      return NULL;

   memcpy(realloc_ptr, ptr, _malloc_usable_size_r(r, ptr));
   _free_r(r, ptr);

   return realloc_ptr;
}