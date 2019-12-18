#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int __r1; int __r2; } ;
typedef  TYPE_1__ mpc_decoder ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpc_decoder_init_quant (TYPE_1__*,float) ; 

void mpc_decoder_setup(mpc_decoder *d)
{
	memset(d, 0, sizeof *d);

	d->__r1 = 1;
	d->__r2 = 1;

	mpc_decoder_init_quant(d, 1.0f);
}