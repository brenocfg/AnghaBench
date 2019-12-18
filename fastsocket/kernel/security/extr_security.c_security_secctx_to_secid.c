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
struct TYPE_2__ {int (* secctx_to_secid ) (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 TYPE_1__* security_ops ; 
 int stub1 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int security_secctx_to_secid(const char *secdata, u32 seclen, u32 *secid)
{
	return security_ops->secctx_to_secid(secdata, seclen, secid);
}