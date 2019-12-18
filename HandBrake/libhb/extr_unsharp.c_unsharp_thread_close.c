#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__*** SC; } ;
typedef  TYPE_1__ unsharp_thread_context_t ;
struct TYPE_7__ {int steps; } ;
typedef  TYPE_2__ unsharp_plane_context_t ;
struct TYPE_8__ {int threads; TYPE_1__** thread_ctx; TYPE_2__* plane_ctx; } ;
typedef  TYPE_3__ hb_filter_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__**) ; 

__attribute__((used)) static void unsharp_thread_close(hb_filter_private_t *pv)
{
    int c, z;
    for (c = 0; c < 3; c++)
    {
        unsharp_plane_context_t * ctx = &pv->plane_ctx[c];
        for (int t = 0; t < pv->threads; t++)
        {
            unsharp_thread_context_t * tctx = &pv->thread_ctx[t][c];
            for (z = 0; z < 2 * ctx->steps; z++)
            {
                free(tctx->SC[z]);
                tctx->SC[z] = NULL;
            }
        }
    }
    free(pv->thread_ctx);
}