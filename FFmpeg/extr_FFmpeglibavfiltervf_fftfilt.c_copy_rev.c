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
typedef  int /*<<< orphan*/  FFTSample ;

/* Variables and functions */

__attribute__((used)) static void copy_rev (FFTSample *dest, int w, int w2)
{
    int i;

    for (i = w; i < w + (w2-w)/2; i++)
        dest[i] = dest[2*w - i - 1];

    for (; i < w2; i++)
        dest[i] = dest[w2 - i];
}