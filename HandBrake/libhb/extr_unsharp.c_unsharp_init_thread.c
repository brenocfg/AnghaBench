#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ ** SC; } ;
typedef  TYPE_1__ unsharp_thread_context_t ;
typedef  int /*<<< orphan*/  unsharp_thread_context3_t ;
struct TYPE_10__ {int steps; int /*<<< orphan*/  width; int /*<<< orphan*/  pix_fmt; } ;
typedef  TYPE_2__ unsharp_plane_context_t ;
struct TYPE_11__ {int threads; TYPE_1__** thread_ctx; TYPE_2__* plane_ctx; } ;
typedef  TYPE_3__ hb_filter_private_t ;
struct TYPE_12__ {TYPE_3__* private_data; } ;
typedef  TYPE_4__ hb_filter_object_t ;

/* Variables and functions */
 TYPE_1__** calloc (int,int) ; 
 int /*<<< orphan*/  hb_error (char*) ; 
 int hb_image_width (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  unsharp_close (TYPE_4__*) ; 
 int /*<<< orphan*/  unsharp_thread_close (TYPE_3__*) ; 

__attribute__((used)) static int unsharp_init_thread(hb_filter_object_t *filter, int threads)
{
    hb_filter_private_t * pv = filter->private_data;

    unsharp_thread_close(pv);
    pv->thread_ctx = calloc(threads, sizeof(unsharp_thread_context3_t));
    pv->threads = threads;
    for (int c = 0; c < 3; c++)
    {
        unsharp_plane_context_t * ctx = &pv->plane_ctx[c];
        int w = hb_image_width(ctx->pix_fmt, ctx->width, c);

        for (int t = 0; t < threads; t++)
        {
            unsharp_thread_context_t * tctx = &pv->thread_ctx[t][c];
            int z;
            for (z = 0; z < 2 * ctx->steps; z++)
            {
                tctx->SC[z] = malloc(sizeof(*(tctx->SC[z])) *
                                     (w + 2 * ctx->steps));
                if (tctx->SC[z] == NULL)
                {
                    hb_error("Unsharp calloc failed");
                    unsharp_close(filter);
                    return -1;
                }
            }
        }
    }
    return 0;
}