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
struct TYPE_4__ {int sign; int bexp; unsigned int mant; } ;
struct TYPE_5__ {TYPE_1__ parts; } ;
typedef  TYPE_2__ ieee754sp ;

/* Variables and functions */
 int SP_EBIAS ; 
 int SP_EMAX ; 
 int SP_EMIN ; 
 unsigned int SP_MBITS ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static inline ieee754sp buildsp(int s, int bx, unsigned m)
{
	ieee754sp r;

	assert((s) == 0 || (s) == 1);
	assert((bx) >= SP_EMIN - 1 + SP_EBIAS
	       && (bx) <= SP_EMAX + 1 + SP_EBIAS);
	assert(((m) >> SP_MBITS) == 0);

	r.parts.sign = s;
	r.parts.bexp = bx;
	r.parts.mant = m;

	return r;
}