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
typedef  int /*<<< orphan*/  u32 ;
struct sa_state_record {int /*<<< orphan*/  save_digest; } ;
struct pd_uinfo {scalar_t__ dest_va; scalar_t__ sr_va; } ;
struct TYPE_3__ {scalar_t__ hash_alg; } ;
struct TYPE_4__ {TYPE_1__ bf; } ;
struct dynamic_sa_ctl {TYPE_2__ sa_command_0; } ;
struct crypto4xx_ctx {scalar_t__ sa_in; } ;

/* Variables and functions */
 scalar_t__ SA_HASH_ALG_SHA1 ; 
 int /*<<< orphan*/  SA_HASH_ALG_SHA1_DIGEST_SIZE ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 crypto4xx_copy_digest_to_dst(struct pd_uinfo *pd_uinfo,
					struct crypto4xx_ctx *ctx)
{
	struct dynamic_sa_ctl *sa = (struct dynamic_sa_ctl *) ctx->sa_in;
	struct sa_state_record *state_record =
				(struct sa_state_record *) pd_uinfo->sr_va;

	if (sa->sa_command_0.bf.hash_alg == SA_HASH_ALG_SHA1) {
		memcpy((void *) pd_uinfo->dest_va, state_record->save_digest,
		       SA_HASH_ALG_SHA1_DIGEST_SIZE);
	}

	return 0;
}