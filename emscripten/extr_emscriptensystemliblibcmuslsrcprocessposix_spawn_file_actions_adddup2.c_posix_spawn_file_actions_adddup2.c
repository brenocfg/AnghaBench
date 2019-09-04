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
struct fdop {int srcfd; int fd; struct fdop* prev; struct fdop* next; int /*<<< orphan*/  cmd; } ;
struct TYPE_3__ {struct fdop* __actions; } ;
typedef  TYPE_1__ posix_spawn_file_actions_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FDOP_DUP2 ; 
 struct fdop* malloc (int) ; 

int posix_spawn_file_actions_adddup2(posix_spawn_file_actions_t *fa, int srcfd, int fd)
{
	struct fdop *op = malloc(sizeof *op);
	if (!op) return ENOMEM;
	op->cmd = FDOP_DUP2;
	op->srcfd = srcfd;
	op->fd = fd;
	if ((op->next = fa->__actions)) op->next->prev = op;
	op->prev = 0;
	fa->__actions = op;
	return 0;
}