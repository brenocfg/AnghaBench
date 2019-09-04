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
struct match {int /*<<< orphan*/  name; struct match* next; } ;

/* Variables and functions */
 struct match* malloc (int) ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int append(struct match **tail, const char *name, size_t len, int mark)
{
	struct match *new = malloc(sizeof(struct match) + len + 1);
	if (!new) return -1;
	(*tail)->next = new;
	new->next = NULL;
	strcpy(new->name, name);
	if (mark) strcat(new->name, "/");
	*tail = new;
	return 0;
}