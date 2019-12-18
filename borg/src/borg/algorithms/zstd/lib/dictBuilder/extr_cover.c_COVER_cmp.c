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
typedef  scalar_t__ U32 ;
struct TYPE_3__ {int /*<<< orphan*/  d; scalar_t__ const samples; } ;
typedef  TYPE_1__ COVER_ctx_t ;

/* Variables and functions */
 int memcmp (scalar_t__ const,scalar_t__ const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int COVER_cmp(COVER_ctx_t *ctx, const void *lp, const void *rp) {
  U32 const lhs = *(U32 const *)lp;
  U32 const rhs = *(U32 const *)rp;
  return memcmp(ctx->samples + lhs, ctx->samples + rhs, ctx->d);
}