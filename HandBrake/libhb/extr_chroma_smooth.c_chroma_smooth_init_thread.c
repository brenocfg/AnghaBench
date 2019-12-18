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
struct TYPE_9__ {int threads; TYPE_3__** thread_ctx; TYPE_4__* plane_ctx; } ;
typedef  TYPE_1__ hb_filter_private_t ;
struct TYPE_10__ {TYPE_1__* private_data; } ;
typedef  TYPE_2__ hb_filter_object_t ;
struct TYPE_11__ {int /*<<< orphan*/ ** SC; } ;
typedef  TYPE_3__ chroma_smooth_thread_context_t ;
typedef  int /*<<< orphan*/  chroma_smooth_thread_context3_t ;
struct TYPE_12__ {int steps; int /*<<< orphan*/  width; int /*<<< orphan*/  pix_fmt; } ;
typedef  TYPE_4__ chroma_smooth_plane_context_t ;

/* Variables and functions */
 TYPE_3__** calloc (int,int) ; 
 int /*<<< orphan*/  chroma_smooth_close (TYPE_2__*) ; 
 int /*<<< orphan*/  chroma_smooth_thread_close (TYPE_1__*) ; 
 int /*<<< orphan*/  hb_error (char*) ; 
 int hb_image_width (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * malloc (int) ; 

__attribute__((used)) static int chroma_smooth_init_thread(hb_filter_object_t *filter, int threads)
{
    hb_filter_private_t * pv = filter->private_data;

    chroma_smooth_thread_close(pv);
    pv->thread_ctx = calloc(threads, sizeof(chroma_smooth_thread_context3_t));
    pv->threads = threads;
    for (int c = 0; c < 3; c++)
    {
        chroma_smooth_plane_context_t * ctx = &pv->plane_ctx[c];
        int w = hb_image_width(ctx->pix_fmt, ctx->width, c);

        for (int t = 0; t < threads; t++)
        {
            chroma_smooth_thread_context_t * tctx = &pv->thread_ctx[t][c];

            if (c)
            {
                int z;
                for (z = 0; z < 2 * ctx->steps; z++)
                {
                    tctx->SC[z] = malloc(sizeof(*(tctx->SC[z])) *
                                         (w + 2 * ctx->steps));
                    if (tctx->SC[z] == NULL)
                    {
                        hb_error("Chroma Smooth calloc failed");
                        chroma_smooth_close(filter);
                        return -1;
                    }
                }
            }
        }
    }
    return 0;
}