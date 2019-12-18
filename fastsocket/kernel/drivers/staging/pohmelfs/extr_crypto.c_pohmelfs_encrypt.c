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
struct pohmelfs_crypto_engine {int /*<<< orphan*/  iv; int /*<<< orphan*/  cipher; struct ablkcipher_request* data; } ;
struct pohmelfs_crypto_thread {struct pohmelfs_crypto_engine eng; struct netfs_trans* trans; } ;
struct netfs_trans {int dummy; } ;
struct ablkcipher_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ablkcipher_request_set_tfm (struct ablkcipher_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ablkcipher_request*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pohmelfs_encrypt_iterator ; 
 int /*<<< orphan*/  pohmelfs_gen_iv (struct netfs_trans*) ; 
 int pohmelfs_trans_iter (struct netfs_trans*,struct pohmelfs_crypto_engine*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pohmelfs_encrypt(struct pohmelfs_crypto_thread *tc)
{
	struct netfs_trans *t = tc->trans;
	struct pohmelfs_crypto_engine *e = &tc->eng;
	struct ablkcipher_request *req = e->data;

	memset(req, 0, sizeof(struct ablkcipher_request));
	ablkcipher_request_set_tfm(req, e->cipher);

	e->iv = pohmelfs_gen_iv(t);

	return pohmelfs_trans_iter(t, e, pohmelfs_encrypt_iterator);
}