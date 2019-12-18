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
struct TYPE_3__ {int* si; float* coeffs; } ;
typedef  TYPE_1__ ccv_cubic_coeffs_t ;

/* Variables and functions */
 int ccv_max (int,int /*<<< orphan*/ ) ; 
 void* ccv_min (int,int) ; 

__attribute__((used)) static void _ccv_init_cubic_coeffs(int si, int sz, float s, ccv_cubic_coeffs_t* coeff)
{
	const float A = -0.75f;
	coeff->si[0] = ccv_max(si - 1, 0);
	coeff->si[1] = si;
	coeff->si[2] = ccv_min(si + 1, sz - 1);
	coeff->si[3] = ccv_min(si + 2, sz - 1);
	float x = s - si;
	coeff->coeffs[0] = ((A * (x + 1) - 5 * A) * (x + 1) + 8 * A) * (x + 1) - 4 * A;
	coeff->coeffs[1] = ((A + 2) * x - (A + 3)) * x * x + 1;
	coeff->coeffs[2] = ((A + 2) * (1 - x) - (A + 3)) * (1 - x) * (1 - x) + 1;
	coeff->coeffs[3] = 1.f - coeff->coeffs[0] - coeff->coeffs[1] - coeff->coeffs[2];
}