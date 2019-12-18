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
typedef  int /*<<< orphan*/  fixed_t ;

/* Variables and functions */
 size_t BOXBOTTOM ; 
 size_t BOXLEFT ; 
 size_t BOXRIGHT ; 
 size_t BOXTOP ; 
 int /*<<< orphan*/  MAXINT ; 
 int /*<<< orphan*/  MININT ; 

void M_ClearBox (fixed_t *box)
{
    box[BOXTOP] = box[BOXRIGHT] = MININT;
    box[BOXBOTTOM] = box[BOXLEFT] = MAXINT;
}