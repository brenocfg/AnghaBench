#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dm_target {char* error; } ;
struct TYPE_3__ {int shift; } ;
struct TYPE_4__ {TYPE_1__ benbi; } ;
struct crypt_config {TYPE_2__ iv_gen_private; int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int crypto_ablkcipher_blocksize (int /*<<< orphan*/ ) ; 
 int ilog2 (unsigned int) ; 

__attribute__((used)) static int crypt_iv_benbi_ctr(struct crypt_config *cc, struct dm_target *ti,
			      const char *opts)
{
	unsigned bs = crypto_ablkcipher_blocksize(cc->tfm);
	int log = ilog2(bs);

	/* we need to calculate how far we must shift the sector count
	 * to get the cipher block count, we use this shift in _gen */

	if (1 << log != bs) {
		ti->error = "cypher blocksize is not a power of 2";
		return -EINVAL;
	}

	if (log > 9) {
		ti->error = "cypher blocksize is > 512";
		return -EINVAL;
	}

	cc->iv_gen_private.benbi.shift = 9 - log;

	return 0;
}