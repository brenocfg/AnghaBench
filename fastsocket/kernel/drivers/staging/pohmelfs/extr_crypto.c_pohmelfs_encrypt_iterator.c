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
typedef  int /*<<< orphan*/  u8 ;
struct scatterlist {int dummy; } ;
struct pohmelfs_crypto_engine {int /*<<< orphan*/  timeout; int /*<<< orphan*/  iv; struct ablkcipher_request* data; } ;
struct ablkcipher_request {int dummy; } ;
typedef  int /*<<< orphan*/  iv ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int pohmelfs_crypto_process (struct ablkcipher_request*,struct scatterlist*,struct scatterlist*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pohmelfs_encrypt_iterator(struct pohmelfs_crypto_engine *e,
		struct scatterlist *sg_dst, struct scatterlist *sg_src)
{
	struct ablkcipher_request *req = e->data;
	u8 iv[32];

	memset(iv, 0, sizeof(iv));

	memcpy(iv, &e->iv, sizeof(e->iv));

	return pohmelfs_crypto_process(req, sg_dst, sg_src, iv, 1, e->timeout);
}