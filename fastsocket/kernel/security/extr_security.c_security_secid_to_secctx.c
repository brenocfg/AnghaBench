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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int (* secid_to_secctx ) (int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 TYPE_1__* security_ops ; 
 int stub1 (int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *) ; 

int security_secid_to_secctx(u32 secid, char **secdata, u32 *seclen)
{
	return security_ops->secid_to_secctx(secid, secdata, seclen);
}