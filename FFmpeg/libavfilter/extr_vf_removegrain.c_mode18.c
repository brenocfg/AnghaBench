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
 int FFMAX (int,int) ; 
 int FFMIN (int const,int const) ; 
 int av_clip (int,int,int) ; 

__attribute__((used)) static int mode18(int c, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
    const int d1 = FFMAX(FFABS(c - a1), FFABS(c - a8));
    const int d2 = FFMAX(FFABS(c - a2), FFABS(c - a7));
    const int d3 = FFMAX(FFABS(c - a3), FFABS(c - a6));
    const int d4 = FFMAX(FFABS(c - a4), FFABS(c - a5));

    const int mindiff = FFMIN(FFMIN(d1, d2), FFMIN(d3, d4));

    if (mindiff == d4) {
        return av_clip(c, FFMIN(a4, a5), FFMAX(a4, a5));
    }
    if (mindiff == d2) {
        return av_clip(c, FFMIN(a2, a7), FFMAX(a2, a7));
    }
    if (mindiff == d3) {
        return av_clip(c, FFMIN(a3, a6), FFMAX(a3, a6));
    }

    return av_clip(c, FFMIN(a1, a8), FFMAX(a1, a8));
}