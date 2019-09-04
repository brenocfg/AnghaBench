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

__attribute__((used)) static inline int check_width (unsigned w0,
                               unsigned w1)
{
    unsigned dw0 = w0;
    w0 *= 8;
    w1 *= 8;
    return(w0 - dw0 <= w1 && w1 <= w0 + dw0);
}