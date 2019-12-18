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
#define  HB_ACODEC_AC3 132 
#define  HB_ACODEC_CA_AAC 131 
#define  HB_ACODEC_CA_HAAC 130 
 int HB_ACODEC_FF_MASK ; 
#define  HB_ACODEC_LAME 129 
#define  HB_ACODEC_VORBIS 128 
 int /*<<< orphan*/  WORK_ENCAVCODEC_AUDIO ; 
 int /*<<< orphan*/  WORK_ENCVORBIS ; 
 int /*<<< orphan*/  WORK_ENC_CA_AAC ; 
 int /*<<< orphan*/  WORK_ENC_CA_HAAC ; 
 int /*<<< orphan*/ * hb_get_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

hb_work_object_t* hb_audio_encoder(hb_handle_t *h, int codec)
{
    if (codec & HB_ACODEC_FF_MASK)
    {
        return hb_get_work(h, WORK_ENCAVCODEC_AUDIO);
    }
    switch (codec)
    {
        case HB_ACODEC_AC3:
        case HB_ACODEC_LAME:    return hb_get_work(h, WORK_ENCAVCODEC_AUDIO);
        case HB_ACODEC_VORBIS:  return hb_get_work(h, WORK_ENCVORBIS);
        case HB_ACODEC_CA_AAC:  return hb_get_work(h, WORK_ENC_CA_AAC);
        case HB_ACODEC_CA_HAAC: return hb_get_work(h, WORK_ENC_CA_HAAC);
        default:                break;
    }
    return NULL;
}