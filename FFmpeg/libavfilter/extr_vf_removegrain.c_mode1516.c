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
 int FFABS (int) ; 
 int /*<<< orphan*/  FFMAX (int,int) ; 
 int FFMIN (int const,int const) ; 
 int av_clip (int const,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mode1516(int c, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
    const int d1 = FFABS(a1 - a8);
    const int d2 = FFABS(a2 - a7);
    const int d3 = FFABS(a3 - a6);

    const int mindiff = FFMIN(FFMIN(d1, d2), d3);
    const int average = (2 * (a2 + a7) + a1 + a3 + a6 + a8 + 4) >> 3;

    if (mindiff == d2) {
        return av_clip(average, FFMIN(a2, a7), FFMAX(a2, a7));
    }
    if (mindiff == d3) {
        return av_clip(average, FFMIN(a3, a6), FFMAX(a3, a6));
    }

    return av_clip(average, FFMIN(a1, a8), FFMAX(a1, a8));
}