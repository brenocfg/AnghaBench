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
struct alias {int flag; char* name; struct alias* next; } ;

/* Variables and functions */
 int ALIASINUSE ; 
 int ATABSIZE ; 
 int /*<<< orphan*/  INTOFF ; 
 int /*<<< orphan*/  INTON ; 
 scalar_t__ aliases ; 
 struct alias** atab ; 
 int /*<<< orphan*/  freealias (struct alias*) ; 

__attribute__((used)) static void
rmaliases(void)
{
	struct alias *ap, **app;
	int i;

	INTOFF;
	for (i = 0; i < ATABSIZE; i++) {
		app = &atab[i];
		while (*app) {
			ap = *app;
			if (ap->flag & ALIASINUSE) {
				*ap->name = '\0';
				app = &(*app)->next;
			} else {
				*app = ap->next;
				freealias(ap);
			}
		}
	}
	aliases = 0;
	INTON;
}