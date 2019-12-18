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
typedef  int /*<<< orphan*/  ieee754dp ;

/* Variables and functions */
 int DPMANT (int /*<<< orphan*/ ) ; 
 int DP_MBIT (scalar_t__) ; 
 scalar_t__ DP_MBITS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee754dp_isnan (int /*<<< orphan*/ ) ; 

int ieee754dp_issnan(ieee754dp x)
{
	assert(ieee754dp_isnan(x));
	return ((DPMANT(x) & DP_MBIT(DP_MBITS-1)) == DP_MBIT(DP_MBITS-1));
}