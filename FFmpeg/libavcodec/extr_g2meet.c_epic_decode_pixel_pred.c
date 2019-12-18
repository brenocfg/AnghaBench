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
typedef  int uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  unsigned_rung; int /*<<< orphan*/  els_ctx; } ;
typedef  TYPE_1__ ePICContext ;

/* Variables and functions */
 int B_shift ; 
 int G_shift ; 
 int R_shift ; 
 int TOSIGNED (unsigned int) ; 
 int /*<<< orphan*/  avpriv_request_sample (int /*<<< orphan*/ *,char*,int,int,int) ; 
 int epic_decode_component_pred (TYPE_1__*,int,int,int) ; 
 unsigned int ff_els_decode_unsigned (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint32_t epic_decode_pixel_pred(ePICContext *dc, int x, int y,
                                       const uint32_t *curr_row,
                                       const uint32_t *above_row)
{
    uint32_t N, W, NW, pred;
    unsigned delta;
    int GN, GW, GNW, R, G, B;

    if (x && y) {
        W  = curr_row[x  - 1];
        N  = above_row[x];
        NW = above_row[x - 1];

        GN  = (N  >> G_shift) & 0xFF;
        GW  = (W  >> G_shift) & 0xFF;
        GNW = (NW >> G_shift) & 0xFF;

        G = epic_decode_component_pred(dc, GN, GW, GNW);

        R = G + epic_decode_component_pred(dc,
                                           ((N  >> R_shift) & 0xFF) - GN,
                                           ((W  >> R_shift) & 0xFF) - GW,
                                           ((NW >> R_shift) & 0xFF) - GNW);

        B = G + epic_decode_component_pred(dc,
                                           ((N  >> B_shift) & 0xFF) - GN,
                                           ((W  >> B_shift) & 0xFF) - GW,
                                           ((NW >> B_shift) & 0xFF) - GNW);
    } else {
        if (x)
            pred = curr_row[x - 1];
        else
            pred = above_row[x];

        delta = ff_els_decode_unsigned(&dc->els_ctx, &dc->unsigned_rung);
        R     = ((pred >> R_shift) & 0xFF) - TOSIGNED(delta);

        delta = ff_els_decode_unsigned(&dc->els_ctx, &dc->unsigned_rung);
        G     = ((pred >> G_shift) & 0xFF) - TOSIGNED(delta);

        delta = ff_els_decode_unsigned(&dc->els_ctx, &dc->unsigned_rung);
        B     = ((pred >> B_shift) & 0xFF) - TOSIGNED(delta);
    }

    if (R<0 || G<0 || B<0 || R > 255 || G > 255 || B > 255) {
        avpriv_request_sample(NULL, "RGB %d %d %d is out of range\n", R, G, B);
        return 0;
    }

    return (R << R_shift) | (G << G_shift) | (B << B_shift);
}