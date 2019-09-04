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
struct socket {TYPE_1__* so_proto; } ;
struct TYPE_2__ {int pr_flags; } ;

/* Variables and functions */
 int PR_ATOMIC ; 

int
sosendallatonce(struct socket *so)
{
	return (so->so_proto->pr_flags & PR_ATOMIC);
}