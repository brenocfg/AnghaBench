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
struct message {struct message* next; int /*<<< orphan*/  msg; } ;

/* Variables and functions */
 struct message* message__list ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct message *mesage__find(const char *msg)
{
	struct message *m = message__list;

	while (m != NULL) {
		if (strcmp(m->msg, msg) == 0)
			break;
		m = m->next;
	}

	return m;
}