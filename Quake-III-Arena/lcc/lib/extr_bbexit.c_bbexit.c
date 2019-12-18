#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* link; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_1__* _bblist ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  profout (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__ tail ; 

__attribute__((used)) static void bbexit(void) {
	FILE *fp;

	if (_bblist != &tail && (fp = fopen("prof.out", "a"))) {
		for ( ; _bblist != &tail; _bblist = _bblist->link)
			profout(_bblist, fp);
		fclose(fp);
	}
}