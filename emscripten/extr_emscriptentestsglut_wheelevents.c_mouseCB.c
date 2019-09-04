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
 int wheel_down ; 
 int wheel_up ; 

void mouseCB(int button, int state, int x, int y)
{
    if(button == 3)
    {
      wheel_up = 1;   
    }
    else if (button == 4)
    {
      wheel_down = 1;
    }
}