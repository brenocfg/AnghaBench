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
struct TYPE_3__ {int /*<<< orphan*/  j2k; } ;
typedef  TYPE_1__ opj_jp2_t ;
typedef  int /*<<< orphan*/  opj_dparameters_t ;

/* Variables and functions */
 int /*<<< orphan*/  j2k_setup_decoder (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void jp2_setup_decoder(opj_jp2_t *jp2, opj_dparameters_t *parameters) {
	/* setup the J2K codec */
	j2k_setup_decoder(jp2->j2k, parameters);
	/* further JP2 initializations go here */
}