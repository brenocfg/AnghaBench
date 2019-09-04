#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xbrfunc_t ;
typedef  size_t uint32_t ;
struct TYPE_4__ {size_t* rgbtoyuv; int n; int /*<<< orphan*/  func; } ;
typedef  TYPE_1__ XBRContext ;
struct TYPE_5__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int FFMAX3 (int,int,int /*<<< orphan*/ ) ; 
 int FFMIN3 (int,int,int) ; 
#define  xbr2x 130 
#define  xbr3x 129 
#define  xbr4x 128 

__attribute__((used)) static int init(AVFilterContext *ctx)
{
    XBRContext *s = ctx->priv;
    static const xbrfunc_t xbrfuncs[] = {xbr2x, xbr3x, xbr4x};

    uint32_t c;
    int bg, rg, g;

    for (bg = -255; bg < 256; bg++) {
        for (rg = -255; rg < 256; rg++) {
            const uint32_t u = (uint32_t)((-169*rg + 500*bg)/1000) + 128;
            const uint32_t v = (uint32_t)(( 500*rg -  81*bg)/1000) + 128;
            int startg = FFMAX3(-bg, -rg, 0);
            int endg = FFMIN3(255-bg, 255-rg, 255);
            uint32_t y = (uint32_t)(( 299*rg + 1000*startg + 114*bg)/1000);
            c = bg + (rg<<16) + 0x010101 * startg;
            for (g = startg; g <= endg; g++) {
                s->rgbtoyuv[c] = ((y++) << 16) + (u << 8) + v;
                c+= 0x010101;
            }
        }
    }

    s->func = xbrfuncs[s->n - 2];
    return 0;
}