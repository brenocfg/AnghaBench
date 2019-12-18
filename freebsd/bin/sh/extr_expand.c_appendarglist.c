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
struct arglist {int count; int capacity; char** args; } ;
typedef  int /*<<< orphan*/  newargs ;

/* Variables and functions */
 int INT_MAX ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  memcpy (char**,char**,int) ; 
 char** stalloc (int) ; 

void
appendarglist(struct arglist *list, char *str)
{
	char **newargs;
	int newcapacity;

	if (list->count >= list->capacity) {
		newcapacity = list->capacity * 2;
		if (newcapacity < 16)
			newcapacity = 16;
		if (newcapacity > INT_MAX / (int)sizeof(newargs[0]))
			error("Too many entries in arglist");
		newargs = stalloc(newcapacity * sizeof(newargs[0]));
		memcpy(newargs, list->args, list->count * sizeof(newargs[0]));
		list->args = newargs;
		list->capacity = newcapacity;
	}
	list->args[list->count++] = str;
}