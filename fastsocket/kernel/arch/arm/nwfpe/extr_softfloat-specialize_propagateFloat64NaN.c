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
typedef  int /*<<< orphan*/  float64 ;
typedef  int flag ;

/* Variables and functions */
 int /*<<< orphan*/  LIT64 (int) ; 
 int float64_is_nan (int /*<<< orphan*/ ) ; 
 int float64_is_signaling_nan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  float_flag_invalid ; 
 int /*<<< orphan*/  float_raise (int /*<<< orphan*/ ) ; 

__attribute__((used)) static float64 propagateFloat64NaN( float64 a, float64 b )
{
    flag aIsNaN, aIsSignalingNaN, bIsNaN, bIsSignalingNaN;

    aIsNaN = float64_is_nan( a );
    aIsSignalingNaN = float64_is_signaling_nan( a );
    bIsNaN = float64_is_nan( b );
    bIsSignalingNaN = float64_is_signaling_nan( b );
    a |= LIT64( 0x0008000000000000 );
    b |= LIT64( 0x0008000000000000 );
    if ( aIsSignalingNaN | bIsSignalingNaN ) float_raise( float_flag_invalid );
    if ( aIsNaN ) {
        return ( aIsSignalingNaN & bIsNaN ) ? b : a;
    }
    else {
        return b;
    }

}