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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  INSERT_WORDS (double,int,int /*<<< orphan*/ ) ; 
 double exp (scalar_t__) ; 
 int k ; 
 scalar_t__ kln2 ; 

double __expo2(double x)
{
	double scale;

	/* note that k is odd and scale*scale overflows */
	INSERT_WORDS(scale, (uint32_t)(0x3ff + k/2) << 20, 0);
	/* exp(x - k ln2) * 2**(k-1) */
	return exp(x - kln2) * scale * scale;
}