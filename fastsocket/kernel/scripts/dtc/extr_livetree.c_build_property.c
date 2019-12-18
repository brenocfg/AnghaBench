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
struct data {int dummy; } ;
struct property {char* name; char* label; int /*<<< orphan*/ * next; struct data val; } ;

/* Variables and functions */
 struct property* xmalloc (int) ; 

struct property *build_property(char *name, struct data val, char *label)
{
	struct property *new = xmalloc(sizeof(*new));

	new->name = name;
	new->val = val;

	new->next = NULL;

	new->label = label;

	return new;
}