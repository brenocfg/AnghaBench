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
struct nbio_stdio_t {int op; size_t len; size_t progress; void* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 void* realloc (void*,size_t) ; 

__attribute__((used)) static void nbio_stdio_resize(void *data, size_t len)
{
   void *new_data              = NULL;
   struct nbio_stdio_t *handle = (struct nbio_stdio_t*)data;
   if (!handle)
      return;

   if (handle->op >= 0)
      abort();
   if (len < handle->len)
      abort();

   handle->len      = len;
   handle->progress = len;
   handle->op       = -1;

   new_data         = realloc(handle->data, handle->len);

   if (new_data)
      handle->data  = new_data;
}