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
struct TYPE_3__ {int lpc_order; int lpc_scaling; int lpc_intbits; int num_channels; int /*<<< orphan*/  gb; int /*<<< orphan*/ ** lpc_coefs; } ;
typedef  TYPE_1__ WmallDecodeCtx ;

/* Variables and functions */
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_sbits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void decode_lpc(WmallDecodeCtx *s)
{
    int ch, i, cbits;
    s->lpc_order   = get_bits(&s->gb, 5) + 1;
    s->lpc_scaling = get_bits(&s->gb, 4);
    s->lpc_intbits = get_bits(&s->gb, 3) + 1;
    cbits = s->lpc_scaling + s->lpc_intbits;
    for (ch = 0; ch < s->num_channels; ch++)
        for (i = 0; i < s->lpc_order; i++)
            s->lpc_coefs[ch][i] = get_sbits(&s->gb, cbits);
}