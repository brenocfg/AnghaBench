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
struct TYPE_3__ {scalar_t__ dtsda_newval; int /*<<< orphan*/  dtsda_option; } ;
typedef  TYPE_1__ dtrace_setoptdata_t ;

/* Variables and functions */
 scalar_t__ DTRACEOPT_UNSET ; 
 int DTRACE_HANDLE_OK ; 
 int g_flowindent ; 
 int g_quiet ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
setopthandler(const dtrace_setoptdata_t *data, void *arg)
{
	if (strcmp(data->dtsda_option, "quiet") == 0)
		g_quiet = data->dtsda_newval != DTRACEOPT_UNSET;

	if (strcmp(data->dtsda_option, "flowindent") == 0)
		g_flowindent = data->dtsda_newval != DTRACEOPT_UNSET;

	return (DTRACE_HANDLE_OK);
}