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
struct TYPE_2__ {struct crypto_blkcipher* data; } ;
struct key {TYPE_1__ payload; int /*<<< orphan*/  type_data; } ;
struct crypto_blkcipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  CRYPTO_ALG_ASYNC ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct crypto_blkcipher*) ; 
 int PTR_ERR (struct crypto_blkcipher*) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  _leave (char*,...) ; 
 struct crypto_blkcipher* crypto_alloc_blkcipher (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_blkcipher_setkey (struct crypto_blkcipher*,void const*,int) ; 
 int /*<<< orphan*/  key_serial (struct key*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,int) ; 

__attribute__((used)) static int rxrpc_instantiate_s(struct key *key, const void *data,
			       size_t datalen)
{
	struct crypto_blkcipher *ci;

	_enter("{%x},,%zu", key_serial(key), datalen);

	if (datalen != 8)
		return -EINVAL;

	memcpy(&key->type_data, data, 8);

	ci = crypto_alloc_blkcipher("pcbc(des)", 0, CRYPTO_ALG_ASYNC);
	if (IS_ERR(ci)) {
		_leave(" = %ld", PTR_ERR(ci));
		return PTR_ERR(ci);
	}

	if (crypto_blkcipher_setkey(ci, data, 8) < 0)
		BUG();

	key->payload.data = ci;
	_leave(" = 0");
	return 0;
}