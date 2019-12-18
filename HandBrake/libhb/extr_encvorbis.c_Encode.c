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
struct TYPE_5__ {int input_samples; int out_discrete_channels; int* remap_table; int /*<<< orphan*/  vd; scalar_t__ buf; int /*<<< orphan*/  pts; int /*<<< orphan*/  list; } ;
typedef  TYPE_1__ hb_work_private_t ;
struct TYPE_6__ {TYPE_1__* private_data; } ;
typedef  TYPE_2__ hb_work_object_t ;
typedef  int /*<<< orphan*/  hb_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/ * Flush (TYPE_2__*) ; 
 int OGGVORBIS_FRAME_SIZE ; 
 int hb_list_bytes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_list_getbytes (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 float** vorbis_analysis_buffer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vorbis_analysis_wrote (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static hb_buffer_t* Encode(hb_work_object_t *w)
{
    hb_work_private_t *pv = w->private_data;
    hb_buffer_t *buf;
    float **buffer;
    int i, j;

    /* Try to extract more data */
    if ((buf = Flush(w)) != NULL)
    {
        return buf;
    }

    /* Check if we need more data */
    if (hb_list_bytes(pv->list) < pv->input_samples * sizeof(float))
    {
        return NULL;
    }

    /* Process more samples */
    hb_list_getbytes(pv->list, pv->buf, pv->input_samples * sizeof(float),
                     &pv->pts, NULL);
    buffer = vorbis_analysis_buffer(&pv->vd, OGGVORBIS_FRAME_SIZE);
    for (i = 0; i < OGGVORBIS_FRAME_SIZE; i++)
    {
        for (j = 0; j < pv->out_discrete_channels; j++)
        {
            buffer[j][i] = ((float*)pv->buf)[(pv->out_discrete_channels * i +
                                              pv->remap_table[j])];
        }
    }

    vorbis_analysis_wrote(&pv->vd, OGGVORBIS_FRAME_SIZE);

    /* Try to extract again */
    return Flush(w);
}