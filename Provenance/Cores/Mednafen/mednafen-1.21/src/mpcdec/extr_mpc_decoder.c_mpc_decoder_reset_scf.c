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
struct TYPE_3__ {int /*<<< orphan*/  SCF_Index_R; int /*<<< orphan*/  SCF_Index_L; } ;
typedef  TYPE_1__ mpc_decoder ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 

void mpc_decoder_reset_scf(mpc_decoder * d, int value)
{
	memset(d->SCF_Index_L, value, sizeof d->SCF_Index_L );
	memset(d->SCF_Index_R, value, sizeof d->SCF_Index_R );
}