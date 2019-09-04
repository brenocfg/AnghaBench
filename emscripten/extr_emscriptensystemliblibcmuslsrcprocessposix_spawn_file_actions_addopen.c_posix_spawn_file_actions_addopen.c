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
struct fdop {int fd; int oflag; struct fdop* prev; struct fdop* next; int /*<<< orphan*/  path; int /*<<< orphan*/  mode; int /*<<< orphan*/  cmd; } ;
struct TYPE_3__ {struct fdop* __actions; } ;
typedef  TYPE_1__ posix_spawn_file_actions_t ;
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FDOP_OPEN ; 
 struct fdop* malloc (scalar_t__) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 

int posix_spawn_file_actions_addopen(posix_spawn_file_actions_t *restrict fa, int fd, const char *restrict path, int flags, mode_t mode)
{
	struct fdop *op = malloc(sizeof *op + strlen(path) + 1);
	if (!op) return ENOMEM;
	op->cmd = FDOP_OPEN;
	op->fd = fd;
	op->oflag = flags;
	op->mode = mode;
	strcpy(op->path, path);
	if ((op->next = fa->__actions)) op->next->prev = op;
	op->prev = 0;
	fa->__actions = op;
	return 0;
}