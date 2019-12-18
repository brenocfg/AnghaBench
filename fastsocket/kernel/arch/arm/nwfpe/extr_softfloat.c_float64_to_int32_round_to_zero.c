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
typedef  int int32 ;
typedef  int int16 ;
typedef  int /*<<< orphan*/  float64 ;
typedef  int flag ;
typedef  int bits64 ;

/* Variables and functions */
 int LIT64 (int) ; 
 int extractFloat64Exp (int /*<<< orphan*/ ) ; 
 int extractFloat64Frac (int /*<<< orphan*/ ) ; 
 int extractFloat64Sign (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  float_flag_inexact ; 
 int /*<<< orphan*/  float_flag_invalid ; 
 int /*<<< orphan*/  float_raise (int /*<<< orphan*/ ) ; 

int32 float64_to_int32_round_to_zero( float64 a )
{
    flag aSign;
    int16 aExp, shiftCount;
    bits64 aSig, savedASig;
    int32 z;

    aSig = extractFloat64Frac( a );
    aExp = extractFloat64Exp( a );
    aSign = extractFloat64Sign( a );
    shiftCount = 0x433 - aExp;
    if ( shiftCount < 21 ) {
        if ( ( aExp == 0x7FF ) && aSig ) aSign = 0;
        goto invalid;
    }
    else if ( 52 < shiftCount ) {
        if ( aExp || aSig ) float_raise( float_flag_inexact );
        return 0;
    }
    aSig |= LIT64( 0x0010000000000000 );
    savedASig = aSig;
    aSig >>= shiftCount;
    z = aSig;
    if ( aSign ) z = - z;
    if ( ( z < 0 ) ^ aSign ) {
 invalid:
        float_raise( float_flag_invalid );
        return aSign ? 0x80000000 : 0x7FFFFFFF;
    }
    if ( ( aSig<<shiftCount ) != savedASig ) {
        float_raise( float_flag_inexact );
    }
    return z;

}