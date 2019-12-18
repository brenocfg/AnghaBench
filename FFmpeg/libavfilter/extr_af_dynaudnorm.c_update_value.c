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
 int /*<<< orphan*/  av_assert0 (int) ; 

__attribute__((used)) static inline double update_value(double new, double old, double aggressiveness)
{
    av_assert0((aggressiveness >= 0.0) && (aggressiveness <= 1.0));
    return aggressiveness * new + (1.0 - aggressiveness) * old;
}