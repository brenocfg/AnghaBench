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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_4__ {scalar_t__* slot; } ;
struct spu_lscsa {TYPE_2__ decr; } ;
struct TYPE_3__ {struct spu_lscsa* lscsa; } ;
struct spu_context {TYPE_1__ csa; } ;

/* Variables and functions */
 int spu_acquire_saved (struct spu_context*) ; 
 int /*<<< orphan*/  spu_release_saved (struct spu_context*) ; 

__attribute__((used)) static int spufs_decr_set(void *data, u64 val)
{
	struct spu_context *ctx = data;
	struct spu_lscsa *lscsa = ctx->csa.lscsa;
	int ret;

	ret = spu_acquire_saved(ctx);
	if (ret)
		return ret;
	lscsa->decr.slot[0] = (u32) val;
	spu_release_saved(ctx);

	return 0;
}