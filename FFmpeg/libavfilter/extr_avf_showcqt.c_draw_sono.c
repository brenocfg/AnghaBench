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
struct TYPE_4__ {int format; int height; int* linesize; scalar_t__* data; } ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
 int AV_PIX_FMT_RGB24 ; 
 int AV_PIX_FMT_YUV420P ; 
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static void draw_sono(AVFrame *out, AVFrame *sono, int off, int idx)
{
    int fmt = out->format, h = sono->height;
    int nb_planes = (fmt == AV_PIX_FMT_RGB24) ? 1 : 3;
    int offh = (fmt == AV_PIX_FMT_YUV420P) ? off / 2 : off;
    int inc = (fmt == AV_PIX_FMT_YUV420P) ? 2 : 1;
    int ls, i, y, yh;

    ls = FFMIN(out->linesize[0], sono->linesize[0]);
    for (y = 0; y < h; y++) {
        memcpy(out->data[0] + (off + y) * out->linesize[0],
               sono->data[0] + (idx + y) % h * sono->linesize[0], ls);
    }

    for (i = 1; i < nb_planes; i++) {
        ls = FFMIN(out->linesize[i], sono->linesize[i]);
        for (y = 0; y < h; y += inc) {
            yh = (fmt == AV_PIX_FMT_YUV420P) ? y / 2 : y;
            memcpy(out->data[i] + (offh + yh) * out->linesize[i],
                   sono->data[i] + (idx + y) % h * sono->linesize[i], ls);
        }
    }
}