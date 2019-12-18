#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_7__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_8__ {TYPE_3__ virt; } ;
struct TYPE_5__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_6__ {TYPE_1__ virt; } ;
struct blkcipher_walk {unsigned int nbytes; void* iv; TYPE_4__ src; TYPE_2__ dst; } ;
struct blkcipher_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DES_BLOCK_SIZE ; 
 int blkcipher_walk_done (struct blkcipher_desc*,struct blkcipher_walk*,unsigned int) ; 
 int blkcipher_walk_virt (struct blkcipher_desc*,struct blkcipher_walk*) ; 
 int crypt_s390_kmc (long,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 

__attribute__((used)) static int cbc_desall_crypt(struct blkcipher_desc *desc, long func,
			    void *param, struct blkcipher_walk *walk)
{
	int ret = blkcipher_walk_virt(desc, walk);
	unsigned int nbytes = walk->nbytes;

	if (!nbytes)
		goto out;

	memcpy(param, walk->iv, DES_BLOCK_SIZE);
	do {
		/* only use complete blocks */
		unsigned int n = nbytes & ~(DES_BLOCK_SIZE - 1);
		u8 *out = walk->dst.virt.addr;
		u8 *in = walk->src.virt.addr;

		ret = crypt_s390_kmc(func, param, out, in, n);
		BUG_ON((ret < 0) || (ret != n));

		nbytes &= DES_BLOCK_SIZE - 1;
		ret = blkcipher_walk_done(desc, walk, nbytes);
	} while ((nbytes = walk->nbytes));
	memcpy(walk->iv, param, DES_BLOCK_SIZE);

out:
	return ret;
}