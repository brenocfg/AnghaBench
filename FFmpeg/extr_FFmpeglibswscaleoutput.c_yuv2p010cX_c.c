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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int int16_t ;
struct TYPE_3__ {scalar_t__ dstFormat; } ;
typedef  TYPE_1__ SwsContext ;

/* Variables and functions */
 scalar_t__ AV_PIX_FMT_P010BE ; 
 int /*<<< orphan*/  output_pixel (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void yuv2p010cX_c(SwsContext *c, const int16_t *chrFilter, int chrFilterSize,
                         const int16_t **chrUSrc, const int16_t **chrVSrc,
                         uint8_t *dest8, int chrDstW)
{
    uint16_t *dest = (uint16_t*)dest8;
    int shift = 17;
    int big_endian = c->dstFormat == AV_PIX_FMT_P010BE;
    int i, j;

    for (i = 0; i < chrDstW; i++) {
        int u = 1 << (shift - 1);
        int v = 1 << (shift - 1);

        for (j = 0; j < chrFilterSize; j++) {
            u += chrUSrc[j][i] * chrFilter[j];
            v += chrVSrc[j][i] * chrFilter[j];
        }

        output_pixel(&dest[2*i]  , u);
        output_pixel(&dest[2*i+1], v);
    }
}