#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int codec_param; } ;
typedef  TYPE_1__ hb_work_object_t ;
typedef  int /*<<< orphan*/  hb_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  hb_error (char*,int,int) ; 
 TYPE_1__* hb_get_work (int /*<<< orphan*/ *,int) ; 

hb_work_object_t* hb_video_decoder(hb_handle_t *h, int vcodec, int param)
{
    hb_work_object_t * w;

    w = hb_get_work(h, vcodec);
    if (w == NULL)
    {
        hb_error("Invalid video decoder: codec %d, param %d", vcodec, param);
        return NULL;
    }
    w->codec_param = param;

    return w;
}