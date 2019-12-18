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
typedef  int /*<<< orphan*/  ulong_t ;
struct TYPE_3__ {int /*<<< orphan*/  pa_file; } ;
typedef  TYPE_1__ dt_printarg_t ;
typedef  int /*<<< orphan*/  ctf_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
dt_print_tag(ctf_id_t base, ulong_t off, dt_printarg_t *pap)
{
	(void) fprintf(pap->pa_file, "<forward decl>");
}