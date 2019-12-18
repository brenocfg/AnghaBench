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
struct scatterlist {int dummy; } ;
struct TYPE_8__ {scalar_t__ addr; } ;
struct TYPE_7__ {TYPE_4__ virt; } ;
struct TYPE_5__ {scalar_t__ addr; } ;
struct TYPE_6__ {TYPE_1__ virt; } ;
struct blkcipher_walk {scalar_t__ nbytes; TYPE_3__ src; TYPE_2__ dst; } ;
struct blkcipher_desc {int dummy; } ;

/* Variables and functions */
 int blkcipher_walk_done (struct blkcipher_desc*,struct blkcipher_walk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blkcipher_walk_init (struct blkcipher_walk*,struct scatterlist*,struct scatterlist*,unsigned int) ; 
 int blkcipher_walk_virt (struct blkcipher_desc*,struct blkcipher_walk*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int skcipher_null_crypt(struct blkcipher_desc *desc,
			       struct scatterlist *dst,
			       struct scatterlist *src, unsigned int nbytes)
{
	struct blkcipher_walk walk;
	int err;

	blkcipher_walk_init(&walk, dst, src, nbytes);
	err = blkcipher_walk_virt(desc, &walk);

	while (walk.nbytes) {
		if (walk.src.virt.addr != walk.dst.virt.addr)
			memcpy(walk.dst.virt.addr, walk.src.virt.addr,
			       walk.nbytes);
		err = blkcipher_walk_done(desc, &walk, 0);
	}

	return err;
}