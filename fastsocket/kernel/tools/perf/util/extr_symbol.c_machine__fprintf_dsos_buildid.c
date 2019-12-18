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
struct machine {int /*<<< orphan*/  user_dsos; int /*<<< orphan*/  kernel_dsos; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t __dsos__fprintf_buildid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

size_t machine__fprintf_dsos_buildid(struct machine *machine, FILE *fp,
				     bool with_hits)
{
	return __dsos__fprintf_buildid(&machine->kernel_dsos, fp, with_hits) +
	       __dsos__fprintf_buildid(&machine->user_dsos, fp, with_hits);
}