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
 scalar_t__ isnan (long double) ; 
 scalar_t__ signbit (long double) ; 

long double fminl(long double x, long double y)
{
	if (isnan(x))
		return y;
	if (isnan(y))
		return x;
	/* handle signed zeros, see C99 Annex F.9.9.2 */
	if (signbit(x) != signbit(y))
		return signbit(x) ? x : y;
	return x < y ? x : y;
}