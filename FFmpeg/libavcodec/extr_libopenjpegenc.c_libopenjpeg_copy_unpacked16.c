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
struct TYPE_12__ {int width; int height; } ;
struct TYPE_11__ {int* linesize; scalar_t__* data; } ;
struct TYPE_9__ {int w; int dx; int dy; int* data; int h; } ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int libopenjpeg_copy_unpacked16(AVCodecContext *avctx, const AVFrame *frame, opj_image_t *image)
{
    int compno;
    int x;
    int y;
    int width;
    int height;
    int *image_line;
    int frame_index;
    const int numcomps = image->numcomps;
    uint16_t *frame_ptr;

    for (compno = 0; compno < numcomps; ++compno) {
        if (image->comps[compno].w > frame->linesize[compno]) {
            av_log(avctx, AV_LOG_ERROR, "Error: frame's linesize is too small for the image\n");
            return 0;
        }
    }

    for (compno = 0; compno < numcomps; ++compno) {
        width     = (avctx->width + image->comps[compno].dx - 1) / image->comps[compno].dx;
        height    = (avctx->height + image->comps[compno].dy - 1) / image->comps[compno].dy;
        frame_ptr = (uint16_t *)frame->data[compno];
        for (y = 0; y < height; ++y) {
            image_line = image->comps[compno].data + y * image->comps[compno].w;
            frame_index = y * (frame->linesize[compno] / 2);
            for (x = 0; x < width; ++x)
                image_line[x] = frame_ptr[frame_index++];
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