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
typedef  double uint8_t ;
struct TYPE_3__ {int* chromakey_uv; double blend; double similarity; } ;
typedef  TYPE_1__ ChromakeyContext ;

/* Variables and functions */
 double av_clipd (double,double,double) ; 
 scalar_t__ sqrt (int) ; 

__attribute__((used)) static uint8_t do_chromakey_pixel(ChromakeyContext *ctx, uint8_t u[9], uint8_t v[9])
{
    double diff = 0.0;
    int du, dv, i;

    for (i = 0; i < 9; ++i) {
        du = (int)u[i] - ctx->chromakey_uv[0];
        dv = (int)v[i] - ctx->chromakey_uv[1];

        diff += sqrt((du * du + dv * dv) / (255.0 * 255.0));
    }

    diff /= 9.0;

    if (ctx->blend > 0.0001) {
        return av_clipd((diff - ctx->similarity) / ctx->blend, 0.0, 1.0) * 255.0;
    } else {
        return (diff > ctx->similarity) ? 255 : 0;
    }
}