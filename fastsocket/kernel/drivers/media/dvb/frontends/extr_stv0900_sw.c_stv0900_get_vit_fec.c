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
struct stv0900_internal {int dummy; } ;
typedef  int s32 ;
typedef  enum fe_stv0900_fec { ____Placeholder_fe_stv0900_fec } fe_stv0900_fec ;
typedef  enum fe_stv0900_demod_num { ____Placeholder_fe_stv0900_demod_num } fe_stv0900_demod_num ;

/* Variables and functions */
 int STV0900_FEC_1_2 ; 
 int STV0900_FEC_2_3 ; 
 int STV0900_FEC_3_4 ; 
 int STV0900_FEC_5_6 ; 
 int STV0900_FEC_6_7 ; 
 int STV0900_FEC_7_8 ; 
 int STV0900_FEC_UNKNOWN ; 
 int /*<<< orphan*/  VIT_CURPUN ; 
 int stv0900_get_bits (struct stv0900_internal*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum fe_stv0900_fec stv0900_get_vit_fec(struct stv0900_internal *intp,
						enum fe_stv0900_demod_num demod)
{
	enum fe_stv0900_fec prate;
	s32 rate_fld = stv0900_get_bits(intp, VIT_CURPUN);

	switch (rate_fld) {
	case 13:
		prate = STV0900_FEC_1_2;
		break;
	case 18:
		prate = STV0900_FEC_2_3;
		break;
	case 21:
		prate = STV0900_FEC_3_4;
		break;
	case 24:
		prate = STV0900_FEC_5_6;
		break;
	case 25:
		prate = STV0900_FEC_6_7;
		break;
	case 26:
		prate = STV0900_FEC_7_8;
		break;
	default:
		prate = STV0900_FEC_UNKNOWN;
		break;
	}

	return prate;
}