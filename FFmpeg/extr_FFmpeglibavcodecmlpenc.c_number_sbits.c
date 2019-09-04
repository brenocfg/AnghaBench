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
 int /*<<< orphan*/  FFABS (int) ; 
 int av_log2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int inline number_sbits(int number)
{
    if (number < 0)
        number++;

    return av_log2(FFABS(number)) + 1 + !!number;
}