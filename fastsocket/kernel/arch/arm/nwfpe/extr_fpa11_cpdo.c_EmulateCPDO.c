#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct roundingData {scalar_t__ exception; int /*<<< orphan*/  precision; int /*<<< orphan*/  mode; } ;
struct TYPE_8__ {unsigned int* fType; TYPE_1__* fpreg; } ;
struct TYPE_7__ {void* fSingle; void* fDouble; int /*<<< orphan*/  fExtended; } ;
typedef  TYPE_1__ FPREG ;
typedef  TYPE_2__ FPA11 ;

/* Variables and functions */
 int /*<<< orphan*/  CONSTANT_FM (unsigned int const) ; 
 unsigned int DoubleCPDO (struct roundingData*,unsigned int const,TYPE_1__*) ; 
 unsigned int ExtendedCPDO (struct roundingData*,unsigned int const,TYPE_1__*) ; 
 TYPE_2__* GET_FPA11 () ; 
 scalar_t__ MONADIC_INSTRUCTION (unsigned int const) ; 
 int /*<<< orphan*/  SetRoundingMode (unsigned int const) ; 
 int /*<<< orphan*/  SetRoundingPrecision (unsigned int const) ; 
 unsigned int SingleCPDO (struct roundingData*,unsigned int const,TYPE_1__*) ; 
 void* float32_to_float64 (void*) ; 
 int /*<<< orphan*/  float32_to_floatx80 (void*) ; 
 void* float64_to_float32 (struct roundingData*,void*) ; 
 int /*<<< orphan*/  float64_to_floatx80 (void*) ; 
 int /*<<< orphan*/  float_raise (scalar_t__) ; 
 void* floatx80_to_float32 (struct roundingData*,int /*<<< orphan*/ ) ; 
 void* floatx80_to_float64 (struct roundingData*,int /*<<< orphan*/ ) ; 
 unsigned int getDestinationSize (unsigned int const) ; 
 size_t getFd (unsigned int const) ; 
 unsigned int getFm (unsigned int const) ; 
 size_t getFn (unsigned int const) ; 
#define  typeDouble 130 
#define  typeExtended 129 
 unsigned int typeNone ; 
#define  typeSingle 128 

unsigned int EmulateCPDO(const unsigned int opcode)
{
	FPA11 *fpa11 = GET_FPA11();
	FPREG *rFd;
	unsigned int nType, nDest, nRc;
	struct roundingData roundData;

	/* Get the destination size.  If not valid let Linux perform
	   an invalid instruction trap. */
	nDest = getDestinationSize(opcode);
	if (typeNone == nDest)
		return 0;

	roundData.mode = SetRoundingMode(opcode);
	roundData.precision = SetRoundingPrecision(opcode);
	roundData.exception = 0;

	/* Compare the size of the operands in Fn and Fm.
	   Choose the largest size and perform operations in that size,
	   in order to make use of all the precision of the operands.
	   If Fm is a constant, we just grab a constant of a size
	   matching the size of the operand in Fn. */
	if (MONADIC_INSTRUCTION(opcode))
		nType = nDest;
	else
		nType = fpa11->fType[getFn(opcode)];

	if (!CONSTANT_FM(opcode)) {
		register unsigned int Fm = getFm(opcode);
		if (nType < fpa11->fType[Fm]) {
			nType = fpa11->fType[Fm];
		}
	}

	rFd = &fpa11->fpreg[getFd(opcode)];

	switch (nType) {
	case typeSingle:
		nRc = SingleCPDO(&roundData, opcode, rFd);
		break;
	case typeDouble:
		nRc = DoubleCPDO(&roundData, opcode, rFd);
		break;
#ifdef CONFIG_FPE_NWFPE_XP
	case typeExtended:
		nRc = ExtendedCPDO(&roundData, opcode, rFd);
		break;
#endif
	default:
		nRc = 0;
	}

	/* The CPDO functions used to always set the destination type
	   to be the same as their working size. */

	if (nRc != 0) {
		/* If the operation succeeded, check to see if the result in the
		   destination register is the correct size.  If not force it
		   to be. */

		fpa11->fType[getFd(opcode)] = nDest;

#ifdef CONFIG_FPE_NWFPE_XP
		if (nDest != nType) {
			switch (nDest) {
			case typeSingle:
				{
					if (typeDouble == nType)
						rFd->fSingle = float64_to_float32(&roundData, rFd->fDouble);
					else
						rFd->fSingle = floatx80_to_float32(&roundData, rFd->fExtended);
				}
				break;

			case typeDouble:
				{
					if (typeSingle == nType)
						rFd->fDouble = float32_to_float64(rFd->fSingle);
					else
						rFd->fDouble = floatx80_to_float64(&roundData, rFd->fExtended);
				}
				break;

			case typeExtended:
				{
					if (typeSingle == nType)
						rFd->fExtended = float32_to_floatx80(rFd->fSingle);
					else
						rFd->fExtended = float64_to_floatx80(rFd->fDouble);
				}
				break;
			}
		}
#else
		if (nDest != nType) {
			if (nDest == typeSingle)
				rFd->fSingle = float64_to_float32(&roundData, rFd->fDouble);
			else
				rFd->fDouble = float32_to_float64(rFd->fSingle);
		}
#endif
	}

	if (roundData.exception)
		float_raise(roundData.exception);

	return nRc;
}