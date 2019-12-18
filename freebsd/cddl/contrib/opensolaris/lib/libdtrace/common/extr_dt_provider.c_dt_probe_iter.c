#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  pr_name; } ;
typedef  TYPE_1__ dt_probe_t ;
struct TYPE_10__ {int /*<<< orphan*/  dtpd_id; int /*<<< orphan*/  dtpd_name; } ;
struct TYPE_8__ {int (* pit_func ) (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  pit_arg; TYPE_4__ pit_desc; int /*<<< orphan*/  pit_hdl; int /*<<< orphan*/  pit_matches; int /*<<< orphan*/  pit_pat; } ;
typedef  TYPE_2__ dt_probe_iter_t ;
typedef  int /*<<< orphan*/  dt_idhash_t ;
struct TYPE_9__ {int /*<<< orphan*/  di_id; TYPE_1__* di_data; } ;
typedef  TYPE_3__ dt_ident_t ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACE_NAMELEN ; 
 int /*<<< orphan*/  dt_gmatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dt_probe_iter(dt_idhash_t *ihp, dt_ident_t *idp, dt_probe_iter_t *pit)
{
	const dt_probe_t *prp = idp->di_data;

	if (!dt_gmatch(prp->pr_name, pit->pit_pat))
		return (0); /* continue on and examine next probe in hash */

	(void) strlcpy(pit->pit_desc.dtpd_name, prp->pr_name, DTRACE_NAMELEN);
	pit->pit_desc.dtpd_id = idp->di_id;
	pit->pit_matches++;

	return (pit->pit_func(pit->pit_hdl, &pit->pit_desc, pit->pit_arg));
}