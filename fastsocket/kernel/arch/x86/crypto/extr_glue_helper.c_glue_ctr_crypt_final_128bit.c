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
typedef  int /*<<< orphan*/  u128 ;
struct TYPE_7__ {scalar_t__ addr; } ;
struct TYPE_8__ {TYPE_3__ virt; } ;
struct TYPE_5__ {scalar_t__ addr; } ;
struct TYPE_6__ {TYPE_1__ virt; } ;
struct blkcipher_walk {unsigned int nbytes; scalar_t__ iv; TYPE_4__ dst; TYPE_2__ src; } ;
struct blkcipher_desc {int /*<<< orphan*/  tfm; } ;
typedef  int /*<<< orphan*/  le128 ;
typedef  int /*<<< orphan*/  (* common_glue_ctr_func_t ) (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  be128 ;

/* Variables and functions */
 int /*<<< orphan*/  be128_to_le128 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* crypto_blkcipher_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le128_to_be128 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void glue_ctr_crypt_final_128bit(const common_glue_ctr_func_t fn_ctr,
					struct blkcipher_desc *desc,
					struct blkcipher_walk *walk)
{
	void *ctx = crypto_blkcipher_ctx(desc->tfm);
	u8 *src = (u8 *)walk->src.virt.addr;
	u8 *dst = (u8 *)walk->dst.virt.addr;
	unsigned int nbytes = walk->nbytes;
	le128 ctrblk;
	u128 tmp;

	be128_to_le128(&ctrblk, (be128 *)walk->iv);

	memcpy(&tmp, src, nbytes);
	fn_ctr(ctx, &tmp, &tmp, &ctrblk);
	memcpy(dst, &tmp, nbytes);

	le128_to_be128((be128 *)walk->iv, &ctrblk);
}