#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  mpc_decoder ;

/* Variables and functions */
 int /*<<< orphan*/  mpc_decoder_scale_output (int /*<<< orphan*/ *,double) ; 

void
mpc_decoder_init_quant(mpc_decoder *d, double scale_factor)
{
    mpc_decoder_scale_output(d, scale_factor);
}