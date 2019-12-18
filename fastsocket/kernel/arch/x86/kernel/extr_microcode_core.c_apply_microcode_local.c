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
struct apply_microcode_ctx {int /*<<< orphan*/  err; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* apply_microcode ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__* microcode_ops ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void apply_microcode_local(void *arg)
{
	struct apply_microcode_ctx *ctx = arg;

	ctx->err = microcode_ops->apply_microcode(smp_processor_id());
}