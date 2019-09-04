#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  Pitch; int /*<<< orphan*/  A; int /*<<< orphan*/  R; int /*<<< orphan*/  G; int /*<<< orphan*/  B; int /*<<< orphan*/  V; int /*<<< orphan*/  U; int /*<<< orphan*/  Y; int /*<<< orphan*/  UV; } ;
struct TYPE_7__ {TYPE_1__ Data; } ;
typedef  TYPE_2__ mfxFrameSurface1 ;
struct TYPE_8__ {int format; int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;
typedef  TYPE_3__ AVFrame ;

/* Variables and functions */
#define  AV_PIX_FMT_NV12 131 
#define  AV_PIX_FMT_RGB32 130 
#define  AV_PIX_FMT_YUV420P 129 
#define  AV_PIX_FMT_YUYV422 128 
 int MFX_ERR_UNSUPPORTED ; 

__attribute__((used)) static int map_frame_to_surface(AVFrame *frame, mfxFrameSurface1 *surface)
{
    switch (frame->format) {
    case AV_PIX_FMT_NV12:
        surface->Data.Y  = frame->data[0];
        surface->Data.UV = frame->data[1];
        break;
    case AV_PIX_FMT_YUV420P:
        surface->Data.Y = frame->data[0];
        surface->Data.U = frame->data[1];
        surface->Data.V = frame->data[2];
        break;
    case AV_PIX_FMT_YUYV422:
        surface->Data.Y = frame->data[0];
        surface->Data.U = frame->data[0] + 1;
        surface->Data.V = frame->data[0] + 3;
        break;
    case AV_PIX_FMT_RGB32:
        surface->Data.B = frame->data[0];
        surface->Data.G = frame->data[0] + 1;
        surface->Data.R = frame->data[0] + 2;
        surface->Data.A = frame->data[0] + 3;
        break;
    default:
        return MFX_ERR_UNSUPPORTED;
    }
    surface->Data.Pitch = frame->linesize[0];

    return 0;
}