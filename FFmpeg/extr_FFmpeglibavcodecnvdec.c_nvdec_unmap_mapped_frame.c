#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_13__ {scalar_t__ data; } ;
struct TYPE_12__ {TYPE_3__* cudl; int /*<<< orphan*/  decoder; TYPE_2__* cvdl; int /*<<< orphan*/  cuda_ctx; TYPE_1__* hw_device_ref; } ;
struct TYPE_11__ {TYPE_7__* decoder_ref; TYPE_7__* idx_ref; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* cuCtxPopCurrent ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* cuCtxPushCurrent ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  (* cuvidUnmapVideoFrame ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {void* data; } ;
typedef  TYPE_4__ NVDECFrame ;
typedef  TYPE_5__ NVDECDecoder ;
typedef  int /*<<< orphan*/  CUdeviceptr ;
typedef  int /*<<< orphan*/  CUcontext ;

/* Variables and functions */
 int CHECK_CU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_buffer_unref (TYPE_7__**) ; 
 int /*<<< orphan*/  av_free (TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvdec_unmap_mapped_frame(void *opaque, uint8_t *data)
{
    NVDECFrame *unmap_data = (NVDECFrame*)data;
    NVDECDecoder *decoder = (NVDECDecoder*)unmap_data->decoder_ref->data;
    void *logctx = decoder->hw_device_ref->data;
    CUdeviceptr devptr = (CUdeviceptr)opaque;
    int ret;
    CUcontext dummy;

    ret = CHECK_CU(decoder->cudl->cuCtxPushCurrent(decoder->cuda_ctx));
    if (ret < 0)
        goto finish;

    CHECK_CU(decoder->cvdl->cuvidUnmapVideoFrame(decoder->decoder, devptr));

    CHECK_CU(decoder->cudl->cuCtxPopCurrent(&dummy));

finish:
    av_buffer_unref(&unmap_data->idx_ref);
    av_buffer_unref(&unmap_data->decoder_ref);
    av_free(unmap_data);
}