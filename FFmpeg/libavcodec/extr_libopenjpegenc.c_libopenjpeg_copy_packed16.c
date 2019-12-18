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
typedef  int uint16_t ;
struct TYPE_10__ {int numcomps; TYPE_1__* comps; } ;
typedef  TYPE_2__ opj_image_t ;
struct TYPE_12__ {int height; int width; } ;
struct TYPE_11__ {int const* linesize; scalar_t__* data; } ;
struct TYPE_9__ {int const w; int* data; int h; } ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int libopenjpeg_copy_packed16(AVCodecContext *avctx, const AVFrame *frame, opj_image_t *image)
{
    int compno;
    int x;
    int y;
    int *image_line;
    int frame_index;
    const int numcomps = image->numcomps;
    uint16_t *frame_ptr = (uint16_t*)frame->data[0];

    for (compno = 0; compno < numcomps; ++compno) {
        if (image->comps[compno].w > frame->linesize[0] / numcomps) {
            av_log(avctx, AV_LOG_ERROR, "Error: frame's linesize is too small for the image\n");
            return 0;
        }
    }

    for (compno = 0; compno < numcomps; ++compno) {
        for (y = 0; y < avctx->height; ++y) {
            image_line = image->comps[compno].data + y * image->comps[compno].w;
            frame_index = y * (frame->linesize[0] / 2) + compno;
            for (x = 0; x < avctx->width; ++x) {
                image_line[x] = frame_ptr[frame_index];
                frame_index += numcomps;
            }
            for (; x < image->comps[compno].w; ++x) {
                image_line[x] = image_line[x - 1];
            }
        }
        for (; y < image->comps[compno].h; ++y) {
            image_line = image->comps[compno].data + y * image->comps[compno].w;
            for (x = 0; x < image->comps[compno].w; ++x) {
                image_line[x] = image_line[x - (int)image->comps[compno].w];
            }
        }
    }

    return 1;
}