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
struct TYPE_2__ {int /*<<< orphan*/  (* cred_transfer ) (struct cred*,struct cred const*) ;} ;

/* Variables and functions */
 TYPE_1__* security_ops ; 
 int /*<<< orphan*/  stub1 (struct cred*,struct cred const*) ; 

void security_transfer_creds(struct cred *new, const struct cred *old)
{
	security_ops->cred_transfer(new, old);
}