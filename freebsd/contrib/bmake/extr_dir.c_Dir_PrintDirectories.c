#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* name; int refCount; int hits; } ;
typedef  TYPE_1__ Path ;
typedef  int /*<<< orphan*/ * LstNode ;

/* Variables and functions */
 int /*<<< orphan*/  Lst_Close (int /*<<< orphan*/ ) ; 
 scalar_t__ Lst_Datum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Lst_Next (int /*<<< orphan*/ ) ; 
 scalar_t__ Lst_Open (int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCESS ; 
 int bigmisses ; 
 int /*<<< orphan*/  debug_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int hits ; 
 int misses ; 
 int nearmisses ; 
 int /*<<< orphan*/  openDirectories ; 

void
Dir_PrintDirectories(void)
{
    LstNode	ln;
    Path	*p;

    fprintf(debug_file, "#*** Directory Cache:\n");
    fprintf(debug_file, "# Stats: %d hits %d misses %d near misses %d losers (%d%%)\n",
	      hits, misses, nearmisses, bigmisses,
	      (hits+bigmisses+nearmisses ?
	       hits * 100 / (hits + bigmisses + nearmisses) : 0));
    fprintf(debug_file, "# %-20s referenced\thits\n", "directory");
    if (Lst_Open(openDirectories) == SUCCESS) {
	while ((ln = Lst_Next(openDirectories)) != NULL) {
	    p = (Path *)Lst_Datum(ln);
	    fprintf(debug_file, "# %-20s %10d\t%4d\n", p->name, p->refCount, p->hits);
	}
	Lst_Close(openDirectories);
    }
}