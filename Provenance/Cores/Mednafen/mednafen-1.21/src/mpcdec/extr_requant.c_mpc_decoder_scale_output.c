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
typedef  int mpc_uint8_t ;
typedef  int mpc_int32_t ;
typedef  int /*<<< orphan*/  mpc_decoder ;

/* Variables and functions */
 int MPC_FIXED_POINT_SHIFT ; 
 int /*<<< orphan*/  SET_SCF (int,double) ; 

void
mpc_decoder_scale_output(mpc_decoder *d, double factor)
{
    mpc_int32_t n; double f1, f2;

#ifndef MPC_FIXED_POINT
    factor *= 1.0 / (double) (1<<(MPC_FIXED_POINT_SHIFT-1));
#else
    factor *= 1.0 / (double) (1<<(16-MPC_FIXED_POINT_SHIFT));
#endif
    f1 = f2 = factor;

    // handles +1.58...-98.41 dB, where's scf[n] / scf[n-1] = 1.20050805774840750476

    SET_SCF(1,factor);

    f1 *=   0.83298066476582673961;
    f2 *= 1/0.83298066476582673961;

    for ( n = 1; n <= 128; n++ ) {
        SET_SCF((mpc_uint8_t)(1+n),f1);
        SET_SCF((mpc_uint8_t)(1-n),f2);
        f1 *=   0.83298066476582673961;
        f2 *= 1/0.83298066476582673961;
    }
}