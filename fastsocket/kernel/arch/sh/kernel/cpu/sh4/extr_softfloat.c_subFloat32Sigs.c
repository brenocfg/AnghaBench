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
typedef  int int16 ;
typedef  int /*<<< orphan*/  float32 ;
typedef  int flag ;
typedef  int bits32 ;

/* Variables and functions */
 scalar_t__ FPSCR_RM_ZERO ; 
 int extractFloat32Exp (int /*<<< orphan*/ ) ; 
 int extractFloat32Frac (int /*<<< orphan*/ ) ; 
 scalar_t__ float_rounding_mode () ; 
 int /*<<< orphan*/  normalizeRoundAndPackFloat32 (int,int,int) ; 
 int /*<<< orphan*/  packFloat32 (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shift32RightJamming (int,int,int*) ; 

__attribute__((used)) static float32 subFloat32Sigs(float32 a, float32 b, flag zSign)
{
	int16 aExp, bExp, zExp;
	bits32 aSig, bSig, zSig;
	int16 expDiff;

	aSig = extractFloat32Frac(a);
	aExp = extractFloat32Exp(a);
	bSig = extractFloat32Frac(b);
	bExp = extractFloat32Exp(b);
	expDiff = aExp - bExp;
	aSig <<= 7;
	bSig <<= 7;
	if (0 < expDiff)
		goto aExpBigger;
	if (expDiff < 0)
		goto bExpBigger;
	if (aExp == 0) {
		aExp = 1;
		bExp = 1;
	}
	if (bSig < aSig)
		goto aBigger;
	if (aSig < bSig)
		goto bBigger;
	return packFloat32(float_rounding_mode() == FPSCR_RM_ZERO, 0, 0);
      bExpBigger:
	if (bExp == 0xFF) {
		return packFloat32(zSign ^ 1, 0xFF, 0);
	}
	if (aExp == 0) {
		++expDiff;
	} else {
		aSig |= 0x40000000;
	}
	shift32RightJamming(aSig, -expDiff, &aSig);
	bSig |= 0x40000000;
      bBigger:
	zSig = bSig - aSig;
	zExp = bExp;
	zSign ^= 1;
	goto normalizeRoundAndPack;
      aExpBigger:
	if (aExp == 0xFF) {
		return a;
	}
	if (bExp == 0) {
		--expDiff;
	} else {
		bSig |= 0x40000000;
	}
	shift32RightJamming(bSig, expDiff, &bSig);
	aSig |= 0x40000000;
      aBigger:
	zSig = aSig - bSig;
	zExp = aExp;
      normalizeRoundAndPack:
	--zExp;
	return normalizeRoundAndPackFloat32(zSign, zExp, zSig);

}