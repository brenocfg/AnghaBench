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
struct cmdnames {scalar_t__ cnt; struct cmdname** names; int /*<<< orphan*/  alloc; } ;
struct cmdname {size_t len; scalar_t__* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct cmdname**,scalar_t__,int /*<<< orphan*/ ) ; 
 struct cmdname* malloc (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char const*,size_t) ; 

void add_cmdname(struct cmdnames *cmds, const char *name, size_t len)
{
	struct cmdname *ent = malloc(sizeof(*ent) + len + 1);

	ent->len = len;
	memcpy(ent->name, name, len);
	ent->name[len] = 0;

	ALLOC_GROW(cmds->names, cmds->cnt + 1, cmds->alloc);
	cmds->names[cmds->cnt++] = ent;
}