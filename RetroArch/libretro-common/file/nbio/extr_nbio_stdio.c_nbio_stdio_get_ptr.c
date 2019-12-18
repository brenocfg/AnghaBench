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
struct nbio_stdio_t {size_t len; int op; void* data; } ;

/* Variables and functions */

__attribute__((used)) static void *nbio_stdio_get_ptr(void *data, size_t* len)
{
   struct nbio_stdio_t *handle = (struct nbio_stdio_t*)data;
   if (!handle)
      return NULL;
   if (len)
      *len = handle->len;
   if (handle->op == -1)
      return handle->data;
   return NULL;
}