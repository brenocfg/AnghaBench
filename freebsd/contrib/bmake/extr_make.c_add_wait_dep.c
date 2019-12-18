#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* name; char* cohort_num; int /*<<< orphan*/  parents; int /*<<< orphan*/  unmade; int /*<<< orphan*/  children; } ;
typedef  TYPE_1__ GNode ;

/* Variables and functions */
 scalar_t__ DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lst_AtEnd (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  MAKE ; 
 int /*<<< orphan*/  debug_file ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  printf (char*,TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static int
add_wait_dep(void *v_cn, void *v_wn)
{
    GNode *cn = v_cn;
    GNode *wn = v_wn;

    if (cn == wn)
	return 1;

    if (cn == NULL || wn == NULL) {
	printf("bad wait dep %p %p\n", cn, wn);
	exit(4);
    }
    if (DEBUG(MAKE))
	 fprintf(debug_file, ".WAIT: add dependency %s%s -> %s\n",
		cn->name, cn->cohort_num, wn->name);

    Lst_AtEnd(wn->children, cn);
    wn->unmade++;
    Lst_AtEnd(cn->parents, wn);
    return 0;
}