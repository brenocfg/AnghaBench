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
struct TYPE_3__ {int resize; int /*<<< orphan*/  egl; } ;
typedef  TYPE_1__ vivante_ctx_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  egl_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void gfx_ctx_vivante_destroy(void *data)
{
   vivante_ctx_data_t *viv = (vivante_ctx_data_t*)data;

   if (viv)
   {
#ifdef HAVE_EGL
      egl_destroy(&viv->egl);
#endif

      viv->resize       = false;
      free(viv);
   }

}