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
struct nbio_stdio_t {scalar_t__ op; struct nbio_stdio_t* data; int /*<<< orphan*/ * f; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct nbio_stdio_t*) ; 

__attribute__((used)) static void nbio_stdio_free(void *data)
{
   struct nbio_stdio_t *handle = (struct nbio_stdio_t*)data;
   if (!handle)
      return;
   if (handle->op >= 0)
      abort();
   fclose(handle->f);
   free(handle->data);

   handle->f    = NULL;
   handle->data = NULL;
   free(handle);
}