#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ccdigest_info {int /*<<< orphan*/  state_size; int /*<<< orphan*/  block_size; } ;
struct ccdigest_ctx {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  b8; } ;
struct TYPE_6__ {int /*<<< orphan*/  b8; } ;
struct TYPE_8__ {TYPE_2__ h; TYPE_1__ m; } ;
typedef  TYPE_3__ SHA1_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ccdigest_data (struct ccdigest_info const*,struct ccdigest_ctx*) ; 
 int ccdigest_nbits (struct ccdigest_info const*,struct ccdigest_ctx*) ; 
 scalar_t__ ccdigest_num (struct ccdigest_info const*,struct ccdigest_ctx*) ; 
 int /*<<< orphan*/  ccdigest_state_ccn (struct ccdigest_info const*,struct ccdigest_ctx*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setCount (TYPE_3__*,scalar_t__) ; 

__attribute__((used)) static void DiToSHA1(const struct ccdigest_info *di, struct ccdigest_ctx *di_ctx, SHA1_CTX *sha1_ctx)
{
	setCount(sha1_ctx, ccdigest_nbits(di, di_ctx)/8+ccdigest_num(di, di_ctx));
	memcpy(sha1_ctx->m.b8, ccdigest_data(di, di_ctx), di->block_size);
	memcpy(sha1_ctx->h.b8, ccdigest_state_ccn(di, di_ctx), di->state_size);
}