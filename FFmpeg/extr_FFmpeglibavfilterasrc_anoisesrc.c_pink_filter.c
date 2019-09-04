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

__attribute__((used)) static double pink_filter(double white, double *buf)
{
    double pink;

    /* http://www.musicdsp.org/files/pink.txt */
    buf[0] = 0.99886 * buf[0] + white * 0.0555179;
    buf[1] = 0.99332 * buf[1] + white * 0.0750759;
    buf[2] = 0.96900 * buf[2] + white * 0.1538520;
    buf[3] = 0.86650 * buf[3] + white * 0.3104856;
    buf[4] = 0.55000 * buf[4] + white * 0.5329522;
    buf[5] = -0.7616 * buf[5] - white * 0.0168980;
    pink = buf[0] + buf[1] + buf[2] + buf[3] + buf[4] + buf[5] + buf[6] + white * 0.5362;
    buf[6] = white * 0.115926;
    return pink * 0.11;
}