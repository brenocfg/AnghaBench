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
struct TYPE_3__ {int /*<<< orphan*/  imag; int /*<<< orphan*/  real; } ;
typedef  TYPE_1__ fft_complex_t ;

/* Variables and functions */
 int /*<<< orphan*/  cosf (float) ; 
 int /*<<< orphan*/  sinf (float) ; 

__attribute__((used)) static fft_complex_t exp_imag(float phase)
{
   fft_complex_t out;
   out.real = cosf(phase);
   out.imag = sinf(phase);
   return out;
}