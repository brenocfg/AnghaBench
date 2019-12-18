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
typedef  TYPE_1__* vfs_context_t ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
struct TYPE_3__ {int /*<<< orphan*/  vc_ucred; } ;

/* Variables and functions */

kauth_cred_t
vfs_context_ucred(vfs_context_t ctx)
{
	return (ctx->vc_ucred);
}