#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ctx; struct TYPE_3__* screen; scalar_t__ socket; } ;
typedef  TYPE_1__ gfx_ctx_osmesa_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  OSMesaDestroyContext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static void osmesa_ctx_destroy(void *data)
{
   gfx_ctx_osmesa_data_t *osmesa = (gfx_ctx_osmesa_data_t*)data;

   if (!osmesa)
      return;

   if (osmesa->socket)
      close(osmesa->socket);

   unlink("/tmp/retroarch-osmesa.fifo");

   free(osmesa->screen);
   OSMesaDestroyContext(osmesa->ctx);

   free(osmesa);
}