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
 int /*<<< orphan*/  av_clipf (float,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float exp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exp_hi ; 
 int /*<<< orphan*/  exp_lo ; 

__attribute__((used)) static void e2_m16(float *s, const int n)
{
    int i;

    for (i = 0; i < n; i++)
        s[i] = exp(av_clipf(s[i], exp_lo, exp_hi));
}