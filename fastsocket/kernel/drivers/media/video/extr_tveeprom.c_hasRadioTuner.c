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

/* Variables and functions */

__attribute__((used)) static int hasRadioTuner(int tunerType)
{
	switch (tunerType) {
	case 18: /* PNPEnv_TUNER_FR1236_MK2 */
	case 23: /* PNPEnv_TUNER_FM1236 */
	case 38: /* PNPEnv_TUNER_FMR1236 */
	case 16: /* PNPEnv_TUNER_FR1216_MK2 */
	case 19: /* PNPEnv_TUNER_FR1246_MK2 */
	case 21: /* PNPEnv_TUNER_FM1216 */
	case 24: /* PNPEnv_TUNER_FM1246 */
	case 17: /* PNPEnv_TUNER_FR1216MF_MK2 */
	case 22: /* PNPEnv_TUNER_FM1216MF */
	case 20: /* PNPEnv_TUNER_FR1256_MK2 */
	case 25: /* PNPEnv_TUNER_FM1256 */
	case 33: /* PNPEnv_TUNER_4039FR5 */
	case 42: /* PNPEnv_TUNER_4009FR5 */
	case 52: /* PNPEnv_TUNER_4049FM5 */
	case 54: /* PNPEnv_TUNER_4049FM5_AltI2C */
	case 44: /* PNPEnv_TUNER_4009FN5 */
	case 31: /* PNPEnv_TUNER_TCPB9085P */
	case 30: /* PNPEnv_TUNER_TCPN9085D */
	case 46: /* PNPEnv_TUNER_TP18NSR01F */
	case 47: /* PNPEnv_TUNER_TP18PSB01D */
	case 49: /* PNPEnv_TUNER_TAPC_I001D */
	case 60: /* PNPEnv_TUNER_TAPE_S001D_MK3 */
	case 57: /* PNPEnv_TUNER_FM1216ME_MK3 */
	case 59: /* PNPEnv_TUNER_FM1216MP_MK3 */
	case 58: /* PNPEnv_TUNER_FM1236_MK3 */
	case 68: /* PNPEnv_TUNER_TAPE_H001F_MK3 */
	case 61: /* PNPEnv_TUNER_TAPE_M001D_MK3 */
	case 78: /* PNPEnv_TUNER_TDA8275C1_8290_FM */
	case 89: /* PNPEnv_TUNER_TCL_MFPE05_2 */
	case 92: /* PNPEnv_TUNER_PHILIPS_FQ1236A_MK4 */
	case 105:
		return 1;
	}
	return 0;
}