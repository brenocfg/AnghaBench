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
typedef  int /*<<< orphan*/  prmap_t ;
struct TYPE_2__ {int /*<<< orphan*/  dpa_count; int /*<<< orphan*/  dpa_proc; } ;
typedef  TYPE_1__ dt_module_cb_arg_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;

/* Variables and functions */
 int /*<<< orphan*/ * Pname_to_ctf (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
dt_module_load_proc_count(void *arg, const prmap_t *prmap, const char *obj)
{
	ctf_file_t *fp;
	dt_module_cb_arg_t *dcp = arg;

	/* Try to grab a ctf container if it exists */
	fp = Pname_to_ctf(dcp->dpa_proc, obj);
	if (fp != NULL)
		dcp->dpa_count++;
	return (0);
}