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
 int const FFMAX (int const,int const) ; 
 int const FFMIN (int const,int const) ; 
 int av_clip (int,int const,int const) ; 

__attribute__((used)) static int mode22(int c, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
    const int l1 = (a1 + a8 + 1) >> 1;
    const int l2 = (a2 + a7 + 1) >> 1;
    const int l3 = (a3 + a6 + 1) >> 1;
    const int l4 = (a4 + a5 + 1) >> 1;

    const int mi = FFMIN(FFMIN(l1, l2), FFMIN(l3, l4));
    const int ma = FFMAX(FFMAX(l1, l2), FFMAX(l3, l4));

    return av_clip(c, mi, ma);
}