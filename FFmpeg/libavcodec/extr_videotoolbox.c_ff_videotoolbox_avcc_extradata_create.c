#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_13__ {int /*<<< orphan*/ * sps; } ;
typedef  TYPE_5__ VTContext ;
struct TYPE_15__ {TYPE_6__* priv_data; TYPE_1__* internal; } ;
struct TYPE_12__ {TYPE_3__* sps; TYPE_2__* pps; } ;
struct TYPE_14__ {TYPE_4__ ps; } ;
struct TYPE_11__ {int data_size; int* data; } ;
struct TYPE_10__ {int data_size; int* data; } ;
struct TYPE_9__ {TYPE_5__* hwaccel_priv_data; } ;
typedef  TYPE_6__ H264Context ;
typedef  int /*<<< orphan*/ * CFDataRef ;
typedef  TYPE_7__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_W8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  AV_WB16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * CFDataCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * av_malloc (int) ; 
 int /*<<< orphan*/  kCFAllocatorDefault ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 

CFDataRef ff_videotoolbox_avcc_extradata_create(AVCodecContext *avctx)
{
    VTContext *vtctx = avctx->internal->hwaccel_priv_data;
    H264Context *h = avctx->priv_data;
    CFDataRef data = NULL;
    uint8_t *p;
    int vt_extradata_size = 6 + 2 + h->ps.sps->data_size + 3 + h->ps.pps->data_size;
    uint8_t *vt_extradata = av_malloc(vt_extradata_size);
    if (!vt_extradata)
        return NULL;

    p = vt_extradata;

    AV_W8(p + 0, 1); /* version */
    AV_W8(p + 1, h->ps.sps->data[1]); /* profile */
    AV_W8(p + 2, h->ps.sps->data[2]); /* profile compat */
    AV_W8(p + 3, h->ps.sps->data[3]); /* level */
    AV_W8(p + 4, 0xff); /* 6 bits reserved (111111) + 2 bits nal size length - 3 (11) */
    AV_W8(p + 5, 0xe1); /* 3 bits reserved (111) + 5 bits number of sps (00001) */
    AV_WB16(p + 6, h->ps.sps->data_size);
    memcpy(p + 8, h->ps.sps->data, h->ps.sps->data_size);
    p += 8 + h->ps.sps->data_size;
    AV_W8(p + 0, 1); /* number of pps */
    AV_WB16(p + 1, h->ps.pps->data_size);
    memcpy(p + 3, h->ps.pps->data, h->ps.pps->data_size);

    p += 3 + h->ps.pps->data_size;
    av_assert0(p - vt_extradata == vt_extradata_size);

    // save sps header (profile/level) used to create decoder session,
    // so we can detect changes and recreate it.
    if (vtctx)
        memcpy(vtctx->sps, h->ps.sps->data + 1, 3);

    data = CFDataCreate(kCFAllocatorDefault, vt_extradata, vt_extradata_size);
    av_free(vt_extradata);
    return data;
}