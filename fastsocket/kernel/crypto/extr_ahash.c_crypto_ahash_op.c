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
struct crypto_ahash {int dummy; } ;
struct ahash_request {scalar_t__ result; } ;

/* Variables and functions */
 int ahash_op_unaligned (struct ahash_request*,int (*) (struct ahash_request*)) ; 
 unsigned long crypto_ahash_alignmask (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 

__attribute__((used)) static int crypto_ahash_op(struct ahash_request *req,
			   int (*op)(struct ahash_request *))
{
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	unsigned long alignmask = crypto_ahash_alignmask(tfm);

	if ((unsigned long)req->result & alignmask)
		return ahash_op_unaligned(req, op);

	return op(req);
}