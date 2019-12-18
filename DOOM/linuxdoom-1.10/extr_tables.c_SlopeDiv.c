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
 int SLOPERANGE ; 

int
SlopeDiv
( unsigned	num,
  unsigned	den)
{
    unsigned 	ans;
    
    if (den < 512)
	return SLOPERANGE;

    ans = (num<<3)/(den>>8);

    return ans <= SLOPERANGE ? ans : SLOPERANGE;
}