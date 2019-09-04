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
struct atfork_funcs {void (* prepare ) () ;void (* parent ) () ;void (* child ) () ;struct atfork_funcs* prev; struct atfork_funcs* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ ) ; 
 struct atfork_funcs* funcs ; 
 int /*<<< orphan*/  lock ; 
 struct atfork_funcs* malloc (int) ; 

int pthread_atfork(void (*prepare)(void), void (*parent)(void), void (*child)(void))
{
	struct atfork_funcs *new = malloc(sizeof *new);
	if (!new) return -1;

	LOCK(lock);
	new->next = funcs;
	new->prev = 0;
	new->prepare = prepare;
	new->parent = parent;
	new->child = child;
	if (funcs) funcs->prev = new;
	funcs = new;
	UNLOCK(lock);
	return 0;
}