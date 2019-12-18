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
struct message {char* msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  message__print_file_lineno (struct message*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void message__print_gettext_msgid_msgstr(struct message *self)
{
	message__print_file_lineno(self);

	printf("msgid %s\n"
	       "msgstr \"\"\n", self->msg);
}