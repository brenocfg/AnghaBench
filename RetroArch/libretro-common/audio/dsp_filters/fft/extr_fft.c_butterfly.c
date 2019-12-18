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
typedef  int /*<<< orphan*/  fft_complex_t ;

/* Variables and functions */
 int /*<<< orphan*/  fft_complex_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fft_complex_mul (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fft_complex_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void butterfly(fft_complex_t *a, fft_complex_t *b, fft_complex_t mod)
{
   mod = fft_complex_mul(mod, *b);
   *b  = fft_complex_sub(*a, mod);
   *a  = fft_complex_add(*a, mod);
}