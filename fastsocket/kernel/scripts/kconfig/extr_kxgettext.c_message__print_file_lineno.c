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
struct message {char* option; struct file_line* files; } ;
struct file_line {char* file; int lineno; struct file_line* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 

__attribute__((used)) static void message__print_file_lineno(struct message *self)
{
	struct file_line *fl = self->files;

	putchar('\n');
	if (self->option != NULL)
		printf("# %s:00000\n", self->option);

	printf("#: %s:%d", fl->file, fl->lineno);
	fl = fl->next;

	while (fl != NULL) {
		printf(", %s:%d", fl->file, fl->lineno);
		fl = fl->next;
	}

	putchar('\n');
}