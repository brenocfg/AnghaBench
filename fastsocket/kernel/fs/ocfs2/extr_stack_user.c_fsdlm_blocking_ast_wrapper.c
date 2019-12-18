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
struct TYPE_4__ {TYPE_1__* sp_proto; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* lp_blocking_ast ) (void*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 TYPE_2__ ocfs2_user_plugin ; 
 int /*<<< orphan*/  stub1 (void*,int) ; 

__attribute__((used)) static void fsdlm_blocking_ast_wrapper(void *astarg, int level)
{
	BUG_ON(ocfs2_user_plugin.sp_proto == NULL);

	ocfs2_user_plugin.sp_proto->lp_blocking_ast(astarg, level);
}