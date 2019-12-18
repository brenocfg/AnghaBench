#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ cr_group_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
struct rsc {int /*<<< orphan*/  client_name; TYPE_2__ cred; scalar_t__ mechctx; TYPE_1__ handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  gss_delete_sec_context (scalar_t__*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_group_info (scalar_t__) ; 

__attribute__((used)) static void rsc_free(struct rsc *rsci)
{
	kfree(rsci->handle.data);
	if (rsci->mechctx)
		gss_delete_sec_context(&rsci->mechctx);
	if (rsci->cred.cr_group_info)
		put_group_info(rsci->cred.cr_group_info);
	kfree(rsci->client_name);
}