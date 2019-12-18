#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* provider; int /*<<< orphan*/  cookie; } ;
typedef  TYPE_2__ nstat_src ;
struct TYPE_8__ {int /*<<< orphan*/ * ncs_provider_filters; } ;
typedef  TYPE_3__ nstat_control_state ;
struct TYPE_6__ {int (* nstat_reporting_allowed ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;size_t nstat_provider_id; } ;

/* Variables and functions */
 int TRUE ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
nstat_control_reporting_allowed(
	nstat_control_state *state,
	nstat_src *src)
{
	if (src->provider->nstat_reporting_allowed == NULL)
		return TRUE;

	return (
	    src->provider->nstat_reporting_allowed(src->cookie,
		&state->ncs_provider_filters[src->provider->nstat_provider_id])
	);
}