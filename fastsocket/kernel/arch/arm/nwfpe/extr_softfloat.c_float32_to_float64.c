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
typedef  int /*<<< orphan*/  float64 ;
typedef  int /*<<< orphan*/  float32 ;
typedef  int /*<<< orphan*/  flag ;
typedef  int bits64 ;
typedef  scalar_t__ bits32 ;

/* Variables and functions */
 int /*<<< orphan*/  commonNaNToFloat64 (int /*<<< orphan*/ ) ; 
 int extractFloat32Exp (int /*<<< orphan*/ ) ; 
 scalar_t__ extractFloat32Frac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extractFloat32Sign (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  float32ToCommonNaN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  normalizeFloat32Subnormal (scalar_t__,int*,scalar_t__*) ; 
 int /*<<< orphan*/  packFloat64 (int /*<<< orphan*/ ,int,int) ; 

float64 float32_to_float64( float32 a )
{
    flag aSign;
    int16 aExp;
    bits32 aSig;

    aSig = extractFloat32Frac( a );
    aExp = extractFloat32Exp( a );
    aSign = extractFloat32Sign( a );
    if ( aExp == 0xFF ) {
        if ( aSig ) return commonNaNToFloat64( float32ToCommonNaN( a ) );
        return packFloat64( aSign, 0x7FF, 0 );
    }
    if ( aExp == 0 ) {
        if ( aSig == 0 ) return packFloat64( aSign, 0, 0 );
        normalizeFloat32Subnormal( aSig, &aExp, &aSig );
        --aExp;
    }
    return packFloat64( aSign, aExp + 0x380, ( (bits64) aSig )<<29 );

}