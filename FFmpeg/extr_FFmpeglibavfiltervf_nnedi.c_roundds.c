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
 int FFMAX (int,int) ; 
 int FFMIN (int,int) ; 
 scalar_t__ ceil (double const) ; 
 double const floor (double const) ; 

__attribute__((used)) static int roundds(const double f)
{
    if (f - floor(f) >= 0.5)
        return FFMIN((int)ceil(f), 32767);
    return FFMAX((int)floor(f), -32768);
}