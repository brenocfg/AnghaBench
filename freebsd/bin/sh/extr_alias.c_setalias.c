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
struct alias {struct alias* next; scalar_t__ flag; void* val; void* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTOFF ; 
 int /*<<< orphan*/  INTON ; 
 int /*<<< orphan*/  aliases ; 
 struct alias* ckmalloc (int) ; 
 struct alias** hashalias (char const*) ; 
 void* savestr (char const*) ; 
 int /*<<< orphan*/  unalias (char const*) ; 

__attribute__((used)) static
void
setalias(const char *name, const char *val)
{
	struct alias *ap, **app;

	unalias(name);
	app = hashalias(name);
	INTOFF;
	ap = ckmalloc(sizeof (struct alias));
	ap->name = savestr(name);
	ap->val = savestr(val);
	ap->flag = 0;
	ap->next = *app;
	*app = ap;
	aliases++;
	INTON;
}