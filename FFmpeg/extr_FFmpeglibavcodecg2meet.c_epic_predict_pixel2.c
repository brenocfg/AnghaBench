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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  stack_pos; int /*<<< orphan*/ * stack; int /*<<< orphan*/  els_ctx; } ;
typedef  TYPE_1__ ePICContext ;

/* Variables and functions */
 size_t EPIC_PIX_STACK_MAX ; 
 scalar_t__ ff_els_decode_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int epic_predict_pixel2(ePICContext *dc, uint8_t *rung,
                               uint32_t *pPix, uint32_t pix)
{
    if (ff_els_decode_bit(&dc->els_ctx, rung)) {
        *pPix = pix;
        return 1;
    }
    dc->stack[dc->stack_pos++ & EPIC_PIX_STACK_MAX] = pix;
    return 0;
}