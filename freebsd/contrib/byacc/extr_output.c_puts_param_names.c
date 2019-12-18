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
struct TYPE_3__ {char* name; struct TYPE_3__* next; } ;
typedef  TYPE_1__ param ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,char*) ; 

__attribute__((used)) static void
puts_param_names(FILE * fp, param *list, int more)
{
    param *p;

    for (p = list; p; p = p->next)
    {
	fprintf(fp, "%s%s", p->name,
		((more || p->next) ? ", " : ""));
    }
}