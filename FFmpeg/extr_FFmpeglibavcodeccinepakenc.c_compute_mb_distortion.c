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
typedef  int uint8_t ;
struct TYPE_3__ {scalar_t__ pix_fmt; } ;
typedef  TYPE_1__ CinepakEncContext ;

/* Variables and functions */
 scalar_t__ AV_PIX_FMT_RGB24 ; 
 int MB_SIZE ; 

__attribute__((used)) static int compute_mb_distortion(CinepakEncContext *s,
                                 uint8_t *a_data[4], int a_linesize[4],
                                 uint8_t *b_data[4], int b_linesize[4])
{
    int x, y, p, d, ret = 0;

    for (y = 0; y < MB_SIZE; y++)
        for (x = 0; x < MB_SIZE; x++) {
            d = a_data[0][x + y * a_linesize[0]] - b_data[0][x + y * b_linesize[0]];
            ret += d * d;
        }

    if (s->pix_fmt == AV_PIX_FMT_RGB24) {
        for (p = 1; p <= 2; p++) {
            for (y = 0; y < MB_SIZE / 2; y++)
                for (x = 0; x < MB_SIZE / 2; x++) {
                    d = a_data[p][x + y * a_linesize[p]] - b_data[p][x + y * b_linesize[p]];
                    ret += d * d;
                }
        }
    }

    return ret;
}