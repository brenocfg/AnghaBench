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
struct spu_context {TYPE_1__* spu; } ;
struct TYPE_2__ {char* local_store; } ;

/* Variables and functions */

__attribute__((used)) static char *spu_hw_get_ls(struct spu_context *ctx)
{
	return ctx->spu->local_store;
}