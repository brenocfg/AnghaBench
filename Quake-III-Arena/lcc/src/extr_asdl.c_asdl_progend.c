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
struct TYPE_3__ {int nuids; int /*<<< orphan*/  nlabels; int /*<<< orphan*/  items; int /*<<< orphan*/  interfaces; } ;

/* Variables and functions */
 int Seq_length (int /*<<< orphan*/ ) ; 
 int assert (scalar_t__) ; 
 int checkuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dopending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  genlabel (int /*<<< orphan*/ ) ; 
 TYPE_1__* pickle ; 
 int /*<<< orphan*/  rcc_write_program (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcsid ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strstr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strtod (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_int (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asdl_progend(void) {
	dopending(NULL);
	{
		int n = checkuid(pickle->interfaces) + Seq_length(pickle->items);
		if (n != pickle->nuids - 1)
			fprintf(stderr, "?bogus uid count: have %d should have %d\n",
				n, pickle->nuids-1);
	}
	pickle->nlabels = genlabel(0);
	write_int((int)(100*(assert(strstr(rcsid, ",v")), strtod(strstr(rcsid, ",v")+2, NULL))
), stdout);
	rcc_write_program(pickle, stdout);
}