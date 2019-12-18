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
struct irqaction {char* name; scalar_t__ dir; } ;
struct irq_desc {int /*<<< orphan*/  dir; } ;

/* Variables and functions */
 int MAX_NAMELEN ; 
 struct irq_desc* irq_to_desc (unsigned int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  name_unique (unsigned int,struct irqaction*) ; 
 scalar_t__ proc_mkdir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

void register_handler_proc(unsigned int irq, struct irqaction *action)
{
	char name [MAX_NAMELEN];
	struct irq_desc *desc = irq_to_desc(irq);

	if (!desc->dir || action->dir || !action->name ||
					!name_unique(irq, action))
		return;

	memset(name, 0, MAX_NAMELEN);
	snprintf(name, MAX_NAMELEN, "%s", action->name);

	/* create /proc/irq/1234/handler/ */
	action->dir = proc_mkdir(name, desc->dir);
}