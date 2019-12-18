#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ right; } ;
struct TYPE_4__ {scalar_t__ left; } ;
struct TYPE_6__ {int type; TYPE_2__ u1; TYPE_1__ u2; } ;
typedef  int /*<<< orphan*/  Reinst ;

/* Variables and functions */
 TYPE_3__* freep ; 

__attribute__((used)) static	Reinst*
newinst(int t)
{
	freep->type = t;
	freep->u2.left = 0;
	freep->u1.right = 0;
	return freep++;
}