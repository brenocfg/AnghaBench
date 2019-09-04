#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * fixed_coef; int /*<<< orphan*/ * exp; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* extract_exponents ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_6__ {int num_blocks; int channels; TYPE_1__ ac3dsp; TYPE_3__* blocks; int /*<<< orphan*/  cpl_on; } ;
typedef  TYPE_2__ AC3EncodeContext ;
typedef  TYPE_3__ AC3Block ;

/* Variables and functions */
 int AC3_MAX_COEFS ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void extract_exponents(AC3EncodeContext *s)
{
    int ch        = !s->cpl_on;
    int chan_size = AC3_MAX_COEFS * s->num_blocks * (s->channels - ch + 1);
    AC3Block *block = &s->blocks[0];

    s->ac3dsp.extract_exponents(block->exp[ch], block->fixed_coef[ch], chan_size);
}