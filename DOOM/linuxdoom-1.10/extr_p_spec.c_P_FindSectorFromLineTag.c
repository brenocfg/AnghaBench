#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ tag; } ;
typedef  TYPE_1__ line_t ;
struct TYPE_5__ {scalar_t__ tag; } ;

/* Variables and functions */
 int numsectors ; 
 TYPE_2__* sectors ; 

int
P_FindSectorFromLineTag
( line_t*	line,
  int		start )
{
    int	i;
	
    for (i=start+1;i<numsectors;i++)
	if (sectors[i].tag == line->tag)
	    return i;
    
    return -1;
}