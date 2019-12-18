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
typedef  int /*<<< orphan*/  u64 ;
struct spu_context {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* signal2_type_get ) (struct spu_context*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct spu_context*) ; 

__attribute__((used)) static u64 spufs_signal2_type_get(struct spu_context *ctx)
{
	return ctx->ops->signal2_type_get(ctx);
}