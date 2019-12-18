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
struct crypto_blkcipher {int dummy; } ;
struct blkcipher_walk {int /*<<< orphan*/  out; scalar_t__ buffer; } ;

/* Variables and functions */
 scalar_t__ ALIGN (unsigned long,unsigned int) ; 
 int /*<<< orphan*/ * blkcipher_get_spot (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int crypto_blkcipher_alignmask (struct crypto_blkcipher*) ; 
 int /*<<< orphan*/  scatterwalk_copychunks (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,int) ; 

__attribute__((used)) static inline unsigned int blkcipher_done_slow(struct crypto_blkcipher *tfm,
					       struct blkcipher_walk *walk,
					       unsigned int bsize)
{
	u8 *addr;
	unsigned int alignmask = crypto_blkcipher_alignmask(tfm);

	addr = (u8 *)ALIGN((unsigned long)walk->buffer, alignmask + 1);
	addr = blkcipher_get_spot(addr, bsize);
	scatterwalk_copychunks(addr, &walk->out, bsize, 1);
	return bsize;
}