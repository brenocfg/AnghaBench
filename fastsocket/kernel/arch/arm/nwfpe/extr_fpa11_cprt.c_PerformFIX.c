#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct roundingData {scalar_t__ exception; int /*<<< orphan*/  precision; int /*<<< orphan*/  mode; } ;
struct TYPE_5__ {int* fType; TYPE_1__* fpreg; } ;
struct TYPE_4__ {int /*<<< orphan*/  fExtended; int /*<<< orphan*/  fDouble; int /*<<< orphan*/  fSingle; } ;
typedef  TYPE_2__ FPA11 ;

/* Variables and functions */
 TYPE_2__* GET_FPA11 () ; 
 int /*<<< orphan*/  SetRoundingMode (unsigned int const) ; 
 int /*<<< orphan*/  SetRoundingPrecision (unsigned int const) ; 
 int /*<<< orphan*/  float32_to_int32 (struct roundingData*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  float64_to_int32 (struct roundingData*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  float_raise (scalar_t__) ; 
 int /*<<< orphan*/  floatx80_to_int32 (struct roundingData*,int /*<<< orphan*/ ) ; 
 unsigned int getFm (unsigned int const) ; 
 int /*<<< orphan*/  getRd (unsigned int const) ; 
#define  typeDouble 130 
#define  typeExtended 129 
#define  typeSingle 128 
 int /*<<< orphan*/  writeRegister (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned int PerformFIX(const unsigned int opcode)
{
	FPA11 *fpa11 = GET_FPA11();
	unsigned int Fn = getFm(opcode);
	struct roundingData roundData;

	roundData.mode = SetRoundingMode(opcode);
	roundData.precision = SetRoundingPrecision(opcode);
	roundData.exception = 0;

	switch (fpa11->fType[Fn]) {
	case typeSingle:
		{
			writeRegister(getRd(opcode), float32_to_int32(&roundData, fpa11->fpreg[Fn].fSingle));
		}
		break;

	case typeDouble:
		{
			writeRegister(getRd(opcode), float64_to_int32(&roundData, fpa11->fpreg[Fn].fDouble));
		}
		break;

#ifdef CONFIG_FPE_NWFPE_XP
	case typeExtended:
		{
			writeRegister(getRd(opcode), floatx80_to_int32(&roundData, fpa11->fpreg[Fn].fExtended));
		}
		break;
#endif

	default:
		return 0;
	}

	if (roundData.exception)
		float_raise(roundData.exception);

	return 1;
}