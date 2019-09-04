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
struct TYPE_3__ {int* colorkey_rgba; double blend; double similarity; } ;
typedef  TYPE_1__ ColorkeyContext ;

/* Variables and functions */
 double av_clipd (double,double,double) ; 
 double sqrt (int) ; 

__attribute__((used)) static uint8_t do_colorkey_pixel(ColorkeyContext *ctx, uint8_t r, uint8_t g, uint8_t b)
{
    int dr = (int)r - ctx->colorkey_rgba[0];
    int dg = (int)g - ctx->colorkey_rgba[1];
    int db = (int)b - ctx->colorkey_rgba[2];

    double diff = sqrt((dr * dr + dg * dg + db * db) / (255.0 * 255.0));

    if (ctx->blend > 0.0001) {
        return av_clipd((diff - ctx->similarity) / ctx->blend, 0.0, 1.0) * 255.0;
    } else {
        return (diff > ctx->similarity) ? 255 : 0;
    }
}