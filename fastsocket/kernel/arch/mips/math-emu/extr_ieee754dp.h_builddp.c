#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_4__ {int sign; int bexp; int mant; } ;
struct TYPE_5__ {TYPE_1__ parts; } ;
typedef  TYPE_2__ ieee754dp ;

/* Variables and functions */
 int DP_EBIAS ; 
 int DP_EMAX ; 
 int DP_EMIN ; 
 int DP_MBITS ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static inline ieee754dp builddp(int s, int bx, u64 m)
{
	ieee754dp r;

	assert((s) == 0 || (s) == 1);
	assert((bx) >= DP_EMIN - 1 + DP_EBIAS
	       && (bx) <= DP_EMAX + 1 + DP_EBIAS);
	assert(((m) >> DP_MBITS) == 0);

	r.parts.sign = s;
	r.parts.bexp = bx;
	r.parts.mant = m;
	return r;
}