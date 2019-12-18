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
struct message {char* option; struct message* files; int /*<<< orphan*/ * next; int /*<<< orphan*/ * msg; } ;

/* Variables and functions */
 struct message* file_line__new (char*,int) ; 
 int /*<<< orphan*/  free (struct message*) ; 
 struct message* malloc (int) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

__attribute__((used)) static struct message *message__new(const char *msg, char *option, char *file, int lineno)
{
	struct message *self = malloc(sizeof(*self));

	if (self == NULL)
		goto out;

	self->files = file_line__new(file, lineno);
	if (self->files == NULL)
		goto out_fail;

	self->msg = strdup(msg);
	if (self->msg == NULL)
		goto out_fail_msg;

	self->option = option;
	self->next = NULL;
out:
	return self;
out_fail_msg:
	free(self->files);
out_fail:
	free(self);
	self = NULL;
	goto out;
}