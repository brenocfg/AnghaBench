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
typedef  TYPE_1__ orbis_ctx_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  egl_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void orbis_ctx_destroy(void *data)
{
    orbis_ctx_data_t *ctx_orbis = (orbis_ctx_data_t *)data;

    if (ctx_orbis)
    {
#ifdef HAVE_EGL
        egl_destroy(&ctx_orbis->egl);
#endif
        ctx_orbis->resize = false;
        free(ctx_orbis);
    }
}