#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  list; int /*<<< orphan*/ * remap; struct TYPE_5__* buf; scalar_t__ converter; } ;
typedef  TYPE_1__ hb_work_private_t ;
struct TYPE_6__ {TYPE_1__* private_data; } ;
typedef  TYPE_2__ hb_work_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  AudioConverterDispose (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  hb_audio_remap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_list_empty (int /*<<< orphan*/ *) ; 

void encCoreAudioClose(hb_work_object_t *w)
{
    hb_work_private_t *pv = w->private_data;

    if (pv != NULL)
    {
        if (pv->converter)
        {
            AudioConverterDispose(pv->converter);
        }
        if (pv->buf != NULL)
        {
            free(pv->buf);
        }
        if (pv->remap != NULL)
        {
            hb_audio_remap_free(pv->remap);
        }
        hb_list_empty(&pv->list);
        free(pv);
        w->private_data = NULL;
    }
}