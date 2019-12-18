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
struct TYPE_3__ {scalar_t__ psm; int /*<<< orphan*/  in_use; } ;
typedef  TYPE_1__ tL2C_RCB ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 

void l2cu_release_rcb (tL2C_RCB *p_rcb)
{
    p_rcb->in_use = FALSE;
    p_rcb->psm    = 0;
}