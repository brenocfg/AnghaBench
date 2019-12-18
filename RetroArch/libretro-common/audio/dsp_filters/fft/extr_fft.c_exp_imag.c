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
struct TYPE_3__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ fft_complex_t ;

/* Variables and functions */
 int /*<<< orphan*/  cos (double) ; 
 int /*<<< orphan*/  sin (double) ; 

__attribute__((used)) static fft_complex_t exp_imag(double phase)
{
   fft_complex_t out = { cos(phase), sin(phase) };
   return out;
}