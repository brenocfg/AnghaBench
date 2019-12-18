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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct crypt_walker_ctx {int length; int /*<<< orphan*/  iv; int /*<<< orphan*/  crypt_ctx; TYPE_1__* ccmode; } ;
typedef  struct crypt_walker_ctx* crypt_walker_ctx_t ;
struct TYPE_2__ {int block_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cccbc_update (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
do_crypt(void *walker, uint8_t *data, uint32_t len)
{
	struct crypt_walker_ctx *wctx = (crypt_walker_ctx_t)walker;
	uint32_t nblocks;

	nblocks = len / wctx->ccmode->block_size;
	assert(len % wctx->ccmode->block_size == 0);
	cccbc_update(wctx->ccmode, wctx->crypt_ctx, wctx->iv, nblocks, data, data);
	wctx->length += len;

	return (0);
}