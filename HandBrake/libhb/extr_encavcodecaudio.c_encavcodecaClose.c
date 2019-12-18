#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * swresample; int /*<<< orphan*/ * list; struct TYPE_8__* input_buf; struct TYPE_8__* output_buf; TYPE_3__* context; } ;
typedef  TYPE_1__ hb_work_private_t ;
struct TYPE_9__ {TYPE_1__* private_data; } ;
typedef  TYPE_2__ hb_work_object_t ;
struct TYPE_10__ {int /*<<< orphan*/ * codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  Finalize (TYPE_2__*) ; 
 int /*<<< orphan*/  avcodec_flush_buffers (TYPE_3__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  hb_avcodec_free_context (TYPE_3__**) ; 
 int /*<<< orphan*/  hb_deep_log (int,char*) ; 
 int /*<<< orphan*/  hb_list_empty (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  swr_free (int /*<<< orphan*/ **) ; 

__attribute__((used)) static void encavcodecaClose(hb_work_object_t * w)
{
    hb_work_private_t * pv = w->private_data;

    if (pv != NULL)
    {
        if (pv->context != NULL)
        {
            Finalize(w);
            hb_deep_log(2, "encavcodecaudio: closing libavcodec");
            if (pv->context->codec != NULL) {
                avcodec_flush_buffers(pv->context);
            }
            hb_avcodec_free_context(&pv->context);
        }

        if (pv->output_buf != NULL)
        {
            free(pv->output_buf);
        }
        if (pv->input_buf != NULL && pv->input_buf != pv->output_buf)
        {
            free(pv->input_buf);
        }
        pv->output_buf = pv->input_buf = NULL;

        if (pv->list != NULL)
        {
            hb_list_empty(&pv->list);
        }

        if (pv->swresample != NULL)
        {
            swr_free(&pv->swresample);
        }

        free(pv);
        w->private_data = NULL;
    }
}