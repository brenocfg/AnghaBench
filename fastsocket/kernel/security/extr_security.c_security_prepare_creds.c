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
struct cred {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int (* cred_prepare ) (struct cred*,struct cred const*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__* security_ops ; 
 int stub1 (struct cred*,struct cred const*,int /*<<< orphan*/ ) ; 

int security_prepare_creds(struct cred *new, const struct cred *old, gfp_t gfp)
{
	return security_ops->cred_prepare(new, old, gfp);
}