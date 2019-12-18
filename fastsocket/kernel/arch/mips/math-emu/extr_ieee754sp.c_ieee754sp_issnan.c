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
typedef  int /*<<< orphan*/  ieee754sp ;

/* Variables and functions */
 int SPMANT (int /*<<< orphan*/ ) ; 
 int SP_MBIT (scalar_t__) ; 
 scalar_t__ SP_MBITS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee754sp_isnan (int /*<<< orphan*/ ) ; 

int ieee754sp_issnan(ieee754sp x)
{
	assert(ieee754sp_isnan(x));
	return (SPMANT(x) & SP_MBIT(SP_MBITS-1));
}