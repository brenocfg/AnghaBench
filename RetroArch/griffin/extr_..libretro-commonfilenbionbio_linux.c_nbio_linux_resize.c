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
struct nbio_linux_t {size_t len; int /*<<< orphan*/  ptr; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 scalar_t__ ftruncate (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  realloc (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void nbio_linux_resize(void *data, size_t len)
{
   struct nbio_linux_t* handle = (struct nbio_linux_t*)data;
   if (!handle)
      return;

   /* This works perfectly fine if this check is removed, but it
    * won't work on other nbio implementations */
   /* therefore, it's blocked so nobody accidentally relies on it */
   if (len < handle->len)
      abort();

   if (ftruncate(handle->fd, len) != 0)
      abort(); /* this one returns void and I can't find any other way
                  for it to report failure */

   handle->ptr = realloc(handle->ptr, len);
   handle->len = len;
}