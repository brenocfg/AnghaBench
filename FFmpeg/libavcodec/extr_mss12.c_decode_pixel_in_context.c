#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  size_t ptrdiff_t ;
struct TYPE_9__ {int (* get_model_sym ) (TYPE_2__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_8__ {int /*<<< orphan*/ ** sec_models; } ;
typedef  TYPE_1__ PixContext ;
typedef  TYPE_2__ ArithCoder ;

/* Variables and functions */
 size_t LEFT ; 
 size_t TOP ; 
 size_t TOP_LEFT ; 
 size_t TOP_RIGHT ; 
 int decode_pixel (TYPE_2__*,TYPE_1__*,scalar_t__*,int,int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,scalar_t__,int) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_pixel_in_context(ArithCoder *acoder, PixContext *pctx,
                                   uint8_t *src, ptrdiff_t stride, int x, int y,
                                   int has_right)
{
    uint8_t neighbours[4];
    uint8_t ref_pix[4];
    int nlen;
    int layer = 0, sub;
    int pix;
    int i, j;

    if (!y) {
        memset(neighbours, src[-1], 4);
    } else {
        neighbours[TOP] = src[-stride];
        if (!x) {
            neighbours[TOP_LEFT] = neighbours[LEFT] = neighbours[TOP];
        } else {
            neighbours[TOP_LEFT] = src[-stride - 1];
            neighbours[    LEFT] = src[-1];
        }
        if (has_right)
            neighbours[TOP_RIGHT] = src[-stride + 1];
        else
            neighbours[TOP_RIGHT] = neighbours[TOP];
    }

    sub = 0;
    if (x >= 2 && src[-2] == neighbours[LEFT])
        sub  = 1;
    if (y >= 2 && src[-2 * stride] == neighbours[TOP])
        sub |= 2;

    nlen = 1;
    ref_pix[0] = neighbours[0];
    for (i = 1; i < 4; i++) {
        for (j = 0; j < nlen; j++)
            if (ref_pix[j] == neighbours[i])
                break;
        if (j == nlen)
            ref_pix[nlen++] = neighbours[i];
    }

    switch (nlen) {
    case 1:
        layer = 0;
        break;
    case 2:
        if (neighbours[TOP] == neighbours[TOP_LEFT]) {
            if (neighbours[TOP_RIGHT] == neighbours[TOP_LEFT])
                layer = 1;
            else if (neighbours[LEFT] == neighbours[TOP_LEFT])
                layer = 2;
            else
                layer = 3;
        } else if (neighbours[TOP_RIGHT] == neighbours[TOP_LEFT]) {
            if (neighbours[LEFT] == neighbours[TOP_LEFT])
                layer = 4;
            else
                layer = 5;
        } else if (neighbours[LEFT] == neighbours[TOP_LEFT]) {
            layer = 6;
        } else {
            layer = 7;
        }
        break;
    case 3:
        if (neighbours[TOP] == neighbours[TOP_LEFT])
            layer = 8;
        else if (neighbours[TOP_RIGHT] == neighbours[TOP_LEFT])
            layer = 9;
        else if (neighbours[LEFT] == neighbours[TOP_LEFT])
            layer = 10;
        else if (neighbours[TOP_RIGHT] == neighbours[TOP])
            layer = 11;
        else if (neighbours[TOP] == neighbours[LEFT])
            layer = 12;
        else
            layer = 13;
        break;
    case 4:
        layer = 14;
        break;
    }

    pix = acoder->get_model_sym(acoder,
                                &pctx->sec_models[layer][sub]);
    if (pix < nlen)
        return ref_pix[pix];
    else
        return decode_pixel(acoder, pctx, ref_pix, nlen, 1);
}