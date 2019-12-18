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
 int D ; 
 scalar_t__ Half ; 
 scalar_t__ I ; 
 scalar_t__ MaxSqEr ; 
 scalar_t__ MinSqEr ; 
 scalar_t__ Radix ; 
 scalar_t__ SQRT (int) ; 
 scalar_t__ SqEr ; 
 scalar_t__ W ; 
 int X ; 
 scalar_t__ X2 ; 
 scalar_t__ X8 ; 
 scalar_t__ Y ; 
 scalar_t__ Y2 ; 
 scalar_t__ Z2 ; 

SR3750()
{
	if (! ((X - Radix < Z2 - Radix) || (X - Z2 > W - Z2))) {
		I = I + 1;
		X2 = SQRT(X * D);
		Y2 = (X2 - Z2) - (Y - Z2);
		X2 = X8 / (Y - Half);
		X2 = X2 - Half * X2 * X2;
		SqEr = (Y2 + Half) + (Half - X2);
		if (SqEr < MinSqEr) MinSqEr = SqEr;
		SqEr = Y2 - X2;
		if (SqEr > MaxSqEr) MaxSqEr = SqEr;
		}
	}