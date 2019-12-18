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
struct tda8083_state {int dummy; } ;
typedef  scalar_t__ fe_spectral_inversion_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ INVERSION_AUTO ; 

__attribute__((used)) static int tda8083_set_inversion (struct tda8083_state* state, fe_spectral_inversion_t inversion)
{
	/*  XXX FIXME: implement other modes than FEC_AUTO */
	if (inversion == INVERSION_AUTO)
		return 0;

	return -EINVAL;
}