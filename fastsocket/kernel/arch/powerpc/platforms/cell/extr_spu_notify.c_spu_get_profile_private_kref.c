#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct spu_context {void* prof_priv_kref; } ;

/* Variables and functions */

void *spu_get_profile_private_kref(struct spu_context *ctx)
{
	return ctx->prof_priv_kref;
}