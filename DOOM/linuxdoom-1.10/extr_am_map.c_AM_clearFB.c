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
 int f_h ; 
 int f_w ; 
 int /*<<< orphan*/  fb ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 

void AM_clearFB(int color)
{
    memset(fb, color, f_w*f_h);
}