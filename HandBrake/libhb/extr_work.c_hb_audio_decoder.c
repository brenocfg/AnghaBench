#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  hb_work_object_t ;
typedef  int /*<<< orphan*/  hb_handle_t ;

/* Variables and functions */
 int HB_ACODEC_FF_MASK ; 
#define  HB_ACODEC_LPCM 128 
 int /*<<< orphan*/  WORK_DECAVCODEC ; 
 int /*<<< orphan*/  WORK_DECLPCM ; 
 int /*<<< orphan*/ * hb_get_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

hb_work_object_t* hb_audio_decoder(hb_handle_t *h, int codec)
{
    hb_work_object_t * w = NULL;
    if (codec & HB_ACODEC_FF_MASK)
    {
        w = hb_get_work(h, WORK_DECAVCODEC);
    }
    switch (codec)
    {
        case HB_ACODEC_LPCM:
            w = hb_get_work(h, WORK_DECLPCM);
            break;
        default:
            break;
    }
    return w;
}