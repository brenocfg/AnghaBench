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
struct TYPE_5__ {TYPE_1__* fpreg; int /*<<< orphan*/ * fType; } ;
struct TYPE_4__ {int /*<<< orphan*/  fExtended; int /*<<< orphan*/  fDouble; int /*<<< orphan*/  fSingle; } ;
typedef  TYPE_2__ FPA11 ;

/* Variables and functions */
 TYPE_2__* GET_FPA11 () ; 
 unsigned int const MASK_ROUNDING_PRECISION ; 
#define  ROUND_DOUBLE 130 
#define  ROUND_EXTENDED 129 
#define  ROUND_SINGLE 128 
 int /*<<< orphan*/  SetRoundingMode (unsigned int const) ; 
 int /*<<< orphan*/  SetRoundingPrecision (unsigned int const) ; 
 int /*<<< orphan*/  float_raise (scalar_t__) ; 
 size_t getFn (unsigned int const) ; 
 int /*<<< orphan*/  getRd (unsigned int const) ; 
 int /*<<< orphan*/  int32_to_float32 (struct roundingData*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int32_to_float64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int32_to_floatx80 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readRegister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typeDouble ; 
 int /*<<< orphan*/  typeExtended ; 
 int /*<<< orphan*/  typeSingle ; 

unsigned int PerformFLT(const unsigned int opcode)
{
	FPA11 *fpa11 = GET_FPA11();
	struct roundingData roundData;

	roundData.mode = SetRoundingMode(opcode);
	roundData.precision = SetRoundingPrecision(opcode);
	roundData.exception = 0;

	switch (opcode & MASK_ROUNDING_PRECISION) {
	case ROUND_SINGLE:
		{
			fpa11->fType[getFn(opcode)] = typeSingle;
			fpa11->fpreg[getFn(opcode)].fSingle = int32_to_float32(&roundData, readRegister(getRd(opcode)));
		}
		break;

	case ROUND_DOUBLE:
		{
			fpa11->fType[getFn(opcode)] = typeDouble;
			fpa11->fpreg[getFn(opcode)].fDouble = int32_to_float64(readRegister(getRd(opcode)));
		}
		break;

#ifdef CONFIG_FPE_NWFPE_XP
	case ROUND_EXTENDED:
		{
			fpa11->fType[getFn(opcode)] = typeExtended;
			fpa11->fpreg[getFn(opcode)].fExtended = int32_to_floatx80(readRegister(getRd(opcode)));
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