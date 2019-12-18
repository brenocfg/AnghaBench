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
struct roundingData {int dummy; } ;
typedef  int /*<<< orphan*/  int32 ;
typedef  int int16 ;
typedef  int /*<<< orphan*/  float64 ;
typedef  scalar_t__ flag ;
typedef  int /*<<< orphan*/  bits64 ;

/* Variables and functions */
 int /*<<< orphan*/  LIT64 (int) ; 
 int extractFloat64Exp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extractFloat64Frac (int /*<<< orphan*/ ) ; 
 scalar_t__ extractFloat64Sign (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roundAndPackInt32 (struct roundingData*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shift64RightJamming (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int32 float64_to_int32( struct roundingData *roundData, float64 a )
{
    flag aSign;
    int16 aExp, shiftCount;
    bits64 aSig;

    aSig = extractFloat64Frac( a );
    aExp = extractFloat64Exp( a );
    aSign = extractFloat64Sign( a );
    if ( ( aExp == 0x7FF ) && aSig ) aSign = 0;
    if ( aExp ) aSig |= LIT64( 0x0010000000000000 );
    shiftCount = 0x42C - aExp;
    if ( 0 < shiftCount ) shift64RightJamming( aSig, shiftCount, &aSig );
    return roundAndPackInt32( roundData, aSign, aSig );

}