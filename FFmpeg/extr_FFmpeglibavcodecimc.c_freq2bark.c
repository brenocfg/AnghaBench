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
 double atan (double) ; 

__attribute__((used)) static inline double freq2bark(double freq)
{
    return 3.5 * atan((freq / 7500.0) * (freq / 7500.0)) + 13.0 * atan(freq * 0.00076);
}