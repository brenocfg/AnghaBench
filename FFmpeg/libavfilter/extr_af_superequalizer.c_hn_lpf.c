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
 int M_PI ; 
 int sinf (int) ; 

__attribute__((used)) static float hn_lpf(int n, float f, float fs)
{
    float t = 1 / fs;
    float omega = 2 * M_PI * f;

    if (n * omega * t == 0)
        return 2 * f * t;
    return 2 * f * t * sinf(n * omega * t) / (n * omega * t);
}