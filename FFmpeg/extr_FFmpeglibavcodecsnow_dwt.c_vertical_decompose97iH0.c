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
typedef  int DWTELEM ;

/* Variables and functions */
 int W_AM ; 
 int W_AO ; 
 int W_AS ; 

__attribute__((used)) static void vertical_decompose97iH0(DWTELEM *b0, DWTELEM *b1, DWTELEM *b2,
                                    int width)
{
    int i;

    for (i = 0; i < width; i++)
        b1[i] -= (W_AM * (b0[i] + b2[i]) + W_AO) >> W_AS;
}