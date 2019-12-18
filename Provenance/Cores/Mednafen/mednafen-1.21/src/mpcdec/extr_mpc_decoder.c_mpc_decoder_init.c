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
typedef  int /*<<< orphan*/  mpc_streaminfo ;
typedef  int /*<<< orphan*/  mpc_decoder ;

/* Variables and functions */
 int /*<<< orphan*/  LUT_DEPTH ; 
 int /*<<< orphan*/  huff_init_lut (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  mpc_decoder_set_streaminfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpc_decoder_setup (int /*<<< orphan*/ *) ; 

mpc_decoder * mpc_decoder_init(mpc_streaminfo *si)
{
	mpc_decoder* p_tmp = malloc(sizeof(mpc_decoder));

	if (p_tmp != 0) {
		mpc_decoder_setup(p_tmp);
		mpc_decoder_set_streaminfo(p_tmp, si);
		huff_init_lut(LUT_DEPTH); // FIXME : this needs to be called only once when the library is loaded
	}

	return p_tmp;
}