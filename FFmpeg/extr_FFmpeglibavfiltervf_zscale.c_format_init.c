#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int depth; int matrix_coefficients; int color_primaries; int transfer_characteristics; int pixel_range; int chroma_location; int /*<<< orphan*/  color_family; int /*<<< orphan*/  pixel_type; int /*<<< orphan*/  subsample_h; int /*<<< orphan*/  subsample_w; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_2__ zimg_image_format ;
struct TYPE_11__ {int /*<<< orphan*/  chroma_location; int /*<<< orphan*/  color_range; int /*<<< orphan*/  color_trc; int /*<<< orphan*/  color_primaries; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_10__ {int flags; TYPE_1__* comp; int /*<<< orphan*/  log2_chroma_h; int /*<<< orphan*/  log2_chroma_w; } ;
struct TYPE_8__ {int depth; } ;
typedef  TYPE_3__ AVPixFmtDescriptor ;
typedef  TYPE_4__ AVFrame ;

/* Variables and functions */
 int AV_PIX_FMT_FLAG_FLOAT ; 
 int AV_PIX_FMT_FLAG_RGB ; 
 int /*<<< orphan*/  ZIMG_COLOR_RGB ; 
 int /*<<< orphan*/  ZIMG_COLOR_YUV ; 
 int ZIMG_MATRIX_RGB ; 
 int /*<<< orphan*/  ZIMG_PIXEL_BYTE ; 
 int /*<<< orphan*/  ZIMG_PIXEL_FLOAT ; 
 int /*<<< orphan*/  ZIMG_PIXEL_WORD ; 
 int ZIMG_RANGE_FULL ; 
 int convert_chroma_location (int /*<<< orphan*/ ) ; 
 int convert_matrix (int /*<<< orphan*/ ) ; 
 int convert_primaries (int /*<<< orphan*/ ) ; 
 int convert_range (int /*<<< orphan*/ ) ; 
 int convert_trc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void format_init(zimg_image_format *format, AVFrame *frame, const AVPixFmtDescriptor *desc,
                        int colorspace, int primaries, int transfer, int range, int location)
{
    format->width = frame->width;
    format->height = frame->height;
    format->subsample_w = desc->log2_chroma_w;
    format->subsample_h = desc->log2_chroma_h;
    format->depth = desc->comp[0].depth;
    format->pixel_type = (desc->flags & AV_PIX_FMT_FLAG_FLOAT) ? ZIMG_PIXEL_FLOAT : desc->comp[0].depth > 8 ? ZIMG_PIXEL_WORD : ZIMG_PIXEL_BYTE;
    format->color_family = (desc->flags & AV_PIX_FMT_FLAG_RGB) ? ZIMG_COLOR_RGB : ZIMG_COLOR_YUV;
    format->matrix_coefficients = (desc->flags & AV_PIX_FMT_FLAG_RGB) ? ZIMG_MATRIX_RGB : colorspace == -1 ? convert_matrix(frame->colorspace) : colorspace;
    format->color_primaries = primaries == -1 ? convert_primaries(frame->color_primaries) : primaries;
    format->transfer_characteristics = transfer == - 1 ? convert_trc(frame->color_trc) : transfer;
    format->pixel_range = (desc->flags & AV_PIX_FMT_FLAG_RGB) ? ZIMG_RANGE_FULL : range == -1 ? convert_range(frame->color_range) : range;
    format->chroma_location = location == -1 ? convert_chroma_location(frame->chroma_location) : location;
}