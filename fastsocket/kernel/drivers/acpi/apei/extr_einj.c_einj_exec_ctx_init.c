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
struct apei_exec_context {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINJ_TAB_ENTRY (TYPE_1__*) ; 
 int /*<<< orphan*/  apei_exec_ctx_init (struct apei_exec_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  einj_ins_type ; 
 TYPE_1__* einj_tab ; 

__attribute__((used)) static void einj_exec_ctx_init(struct apei_exec_context *ctx)
{
	apei_exec_ctx_init(ctx, einj_ins_type, ARRAY_SIZE(einj_ins_type),
			   EINJ_TAB_ENTRY(einj_tab), einj_tab->entries);
}