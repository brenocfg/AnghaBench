#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int type; } ;
typedef  TYPE_1__ GNode ;
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int OP_DOUBLEDEP ; 
 int OP_PRECIOUS ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ allPrecious ; 

Boolean
Targ_Precious(GNode *gn)
{
    if (allPrecious || (gn->type & (OP_PRECIOUS|OP_DOUBLEDEP))) {
	return (TRUE);
    } else {
	return (FALSE);
    }
}