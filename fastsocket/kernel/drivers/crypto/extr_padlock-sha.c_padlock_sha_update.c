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
typedef  int /*<<< orphan*/  u8 ;
struct shash_desc {int flags; } ;
struct TYPE_2__ {int flags; } ;
struct padlock_sha_desc {TYPE_1__ fallback; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int crypto_shash_update (TYPE_1__*,int /*<<< orphan*/  const*,unsigned int) ; 
 struct padlock_sha_desc* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int padlock_sha_update(struct shash_desc *desc,
			      const u8 *data, unsigned int length)
{
	struct padlock_sha_desc *dctx = shash_desc_ctx(desc);

	dctx->fallback.flags = desc->flags & CRYPTO_TFM_REQ_MAY_SLEEP;
	return crypto_shash_update(&dctx->fallback, data, length);
}