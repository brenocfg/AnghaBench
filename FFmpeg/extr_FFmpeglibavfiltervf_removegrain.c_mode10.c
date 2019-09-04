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
 int const FFMIN (int const,int const) ; 

__attribute__((used)) static int mode10(int c, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
    const int d1 = FFABS(c - a1);
    const int d2 = FFABS(c - a2);
    const int d3 = FFABS(c - a3);
    const int d4 = FFABS(c - a4);
    const int d5 = FFABS(c - a5);
    const int d6 = FFABS(c - a6);
    const int d7 = FFABS(c - a7);
    const int d8 = FFABS(c - a8);

    const int mindiff = FFMIN(FFMIN(FFMIN(d1, d2), FFMIN(d3, d4)),
                              FFMIN(FFMIN(d5, d6), FFMIN(d7, d8)));

    if (mindiff == d7) return a7;
    if (mindiff == d8) return a8;
    if (mindiff == d6) return a6;
    if (mindiff == d2) return a2;
    if (mindiff == d3) return a3;
    if (mindiff == d1) return a1;
    if (mindiff == d5) return a5;

    return a4;
}