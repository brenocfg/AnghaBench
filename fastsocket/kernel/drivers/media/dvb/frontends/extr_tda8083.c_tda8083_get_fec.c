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
typedef  size_t u8 ;
struct tda8083_state {int dummy; } ;
typedef  int /*<<< orphan*/  fe_code_rate_t ;

/* Variables and functions */
#define  FEC_1_2 135 
#define  FEC_2_3 134 
#define  FEC_3_4 133 
#define  FEC_4_5 132 
#define  FEC_5_6 131 
#define  FEC_6_7 130 
#define  FEC_7_8 129 
#define  FEC_8_9 128 
 int tda8083_readreg (struct tda8083_state*,int) ; 

__attribute__((used)) static fe_code_rate_t tda8083_get_fec (struct tda8083_state* state)
{
	u8 index;
	static fe_code_rate_t fec_tab [] = { FEC_8_9, FEC_1_2, FEC_2_3, FEC_3_4,
				       FEC_4_5, FEC_5_6, FEC_6_7, FEC_7_8 };

	index = tda8083_readreg(state, 0x0e) & 0x07;

	return fec_tab [index];
}