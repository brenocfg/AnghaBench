#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* sighand; int /*<<< orphan*/  blocked; } ;
struct TYPE_7__ {TYPE_2__* action; } ;
struct TYPE_5__ {scalar_t__ sa_handler; } ;
struct TYPE_6__ {TYPE_1__ sa; } ;

/* Variables and functions */
 scalar_t__ SIG_IGN ; 
 TYPE_4__* current ; 
 scalar_t__ sigismember (int /*<<< orphan*/ *,int) ; 

int is_ignored(int sig)
{
	return (sigismember(&current->blocked, sig) ||
		current->sighand->action[sig-1].sa.sa_handler == SIG_IGN);
}