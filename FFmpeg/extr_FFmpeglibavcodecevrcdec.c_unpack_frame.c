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
struct TYPE_5__ {void* energy_gain; void** lsp; void** fcb_gain; void*** fcb_shape; void** acb_gain; void* pitch_delay; void* tty; void* delay_diff; void* lpc_flag; } ;
struct TYPE_4__ {int bitrate; int /*<<< orphan*/  gb; TYPE_2__ frame; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ EVRCContext ;
typedef  TYPE_2__ EVRCAFrame ;

/* Variables and functions */
#define  RATE_FULL 130 
#define  RATE_HALF 129 
#define  RATE_QUANT 128 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 void* get_bits1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void unpack_frame(EVRCContext *e)
{
    EVRCAFrame *frame = &e->frame;
    GetBitContext *gb = &e->gb;

    switch (e->bitrate) {
    case RATE_FULL:
        frame->lpc_flag        = get_bits1(gb);
        frame->lsp[0]          = get_bits(gb,  6);
        frame->lsp[1]          = get_bits(gb,  6);
        frame->lsp[2]          = get_bits(gb,  9);
        frame->lsp[3]          = get_bits(gb,  7);
        frame->pitch_delay     = get_bits(gb,  7);
        frame->delay_diff      = get_bits(gb,  5);
        frame->acb_gain[0]     = get_bits(gb,  3);
        frame->fcb_shape[0][0] = get_bits(gb,  8);
        frame->fcb_shape[0][1] = get_bits(gb,  8);
        frame->fcb_shape[0][2] = get_bits(gb,  8);
        frame->fcb_shape[0][3] = get_bits(gb, 11);
        frame->fcb_gain[0]     = get_bits(gb,  5);
        frame->acb_gain[1]     = get_bits(gb,  3);
        frame->fcb_shape[1][0] = get_bits(gb,  8);
        frame->fcb_shape[1][1] = get_bits(gb,  8);
        frame->fcb_shape[1][2] = get_bits(gb,  8);
        frame->fcb_shape[1][3] = get_bits(gb, 11);
        frame->fcb_gain    [1] = get_bits(gb,  5);
        frame->acb_gain    [2] = get_bits(gb,  3);
        frame->fcb_shape[2][0] = get_bits(gb,  8);
        frame->fcb_shape[2][1] = get_bits(gb,  8);
        frame->fcb_shape[2][2] = get_bits(gb,  8);
        frame->fcb_shape[2][3] = get_bits(gb, 11);
        frame->fcb_gain    [2] = get_bits(gb,  5);
        frame->tty             = get_bits1(gb);
        break;
    case RATE_HALF:
        frame->lsp         [0] = get_bits(gb,  7);
        frame->lsp         [1] = get_bits(gb,  7);
        frame->lsp         [2] = get_bits(gb,  8);
        frame->pitch_delay     = get_bits(gb,  7);
        frame->acb_gain    [0] = get_bits(gb,  3);
        frame->fcb_shape[0][0] = get_bits(gb, 10);
        frame->fcb_gain    [0] = get_bits(gb,  4);
        frame->acb_gain    [1] = get_bits(gb,  3);
        frame->fcb_shape[1][0] = get_bits(gb, 10);
        frame->fcb_gain    [1] = get_bits(gb,  4);
        frame->acb_gain    [2] = get_bits(gb,  3);
        frame->fcb_shape[2][0] = get_bits(gb, 10);
        frame->fcb_gain    [2] = get_bits(gb,  4);
        break;
    case RATE_QUANT:
        frame->lsp         [0] = get_bits(gb, 4);
        frame->lsp         [1] = get_bits(gb, 4);
        frame->energy_gain     = get_bits(gb, 8);
        break;
    }
}