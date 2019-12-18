#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {scalar_t__ pix_fmt; } ;
typedef  TYPE_1__ CinepakEncContext ;

/* Variables and functions */
 scalar_t__ AV_PIX_FMT_RGB24 ; 

__attribute__((used)) static void get_sub_picture(CinepakEncContext *s, int x, int y,
                            uint8_t * in_data[4], int  in_linesize[4],
                            uint8_t *out_data[4], int out_linesize[4])
{
    out_data[0]     = in_data[0] + x + y * in_linesize[0];
    out_linesize[0] = in_linesize[0];

    if (s->pix_fmt == AV_PIX_FMT_RGB24) {
        out_data[1]     = in_data[1] + (x >> 1) + (y >> 1) * in_linesize[1];
        out_linesize[1] = in_linesize[1];

        out_data[2]     = in_data[2] + (x >> 1) + (y >> 1) * in_linesize[2];
        out_linesize[2] = in_linesize[2];
    }
}