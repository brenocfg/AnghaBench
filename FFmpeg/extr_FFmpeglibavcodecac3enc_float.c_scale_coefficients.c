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
struct TYPE_4__ {int /*<<< orphan*/  (* float_to_fixed24 ) (scalar_t__,scalar_t__,int) ;} ;
struct TYPE_5__ {int num_blocks; int cpl_on; int channels; scalar_t__ mdct_coef_buffer; scalar_t__ fixed_coef_buffer; TYPE_1__ ac3dsp; } ;
typedef  TYPE_2__ AC3EncodeContext ;

/* Variables and functions */
 int AC3_MAX_COEFS ; 
 int /*<<< orphan*/  stub1 (scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static void scale_coefficients(AC3EncodeContext *s)
{
    int chan_size = AC3_MAX_COEFS * s->num_blocks;
    int cpl       = s->cpl_on;
    s->ac3dsp.float_to_fixed24(s->fixed_coef_buffer + (chan_size * !cpl),
                               s->mdct_coef_buffer  + (chan_size * !cpl),
                               chan_size * (s->channels + cpl));
}