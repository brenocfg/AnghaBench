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
typedef  int /*<<< orphan*/  ceiling_t ;

/* Variables and functions */
 int MAXCEILINGS ; 
 int /*<<< orphan*/ ** activeceilings ; 

void P_AddActiveCeiling(ceiling_t* c)
{
    int		i;
    
    for (i = 0; i < MAXCEILINGS;i++)
    {
	if (activeceilings[i] == NULL)
	{
	    activeceilings[i] = c;
	    return;
	}
    }
}