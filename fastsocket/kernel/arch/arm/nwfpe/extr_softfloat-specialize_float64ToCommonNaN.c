#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int float64 ;
struct TYPE_3__ {int sign; int high; scalar_t__ low; } ;
typedef  TYPE_1__ commonNaNT ;

/* Variables and functions */
 scalar_t__ float64_is_signaling_nan (int) ; 
 int /*<<< orphan*/  float_flag_invalid ; 
 int /*<<< orphan*/  float_raise (int /*<<< orphan*/ ) ; 

__attribute__((used)) static commonNaNT float64ToCommonNaN( float64 a )
{
    commonNaNT z;

    if ( float64_is_signaling_nan( a ) ) float_raise( float_flag_invalid );
    z.sign = a>>63;
    z.low = 0;
    z.high = a<<12;
    return z;

}