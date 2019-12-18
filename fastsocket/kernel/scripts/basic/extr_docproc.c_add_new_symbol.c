#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct symfile {int symbolcnt; TYPE_1__* symbollist; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_1__* realloc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  strdup (char*) ; 

__attribute__((used)) static void add_new_symbol(struct symfile *sym, char * symname)
{
	sym->symbollist =
          realloc(sym->symbollist, (sym->symbolcnt + 1) * sizeof(char *));
	sym->symbollist[sym->symbolcnt++].name = strdup(symname);
}