#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vfs_context_t ;
struct fileglob {TYPE_1__* fg_ops; } ;
struct TYPE_2__ {int (* fo_close ) (struct fileglob*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (struct fileglob*,int /*<<< orphan*/ ) ; 

int
fo_close(struct fileglob *fg, vfs_context_t ctx)
{
	return((*fg->fg_ops->fo_close)(fg, ctx));
}