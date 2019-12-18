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
struct hash_desc {int /*<<< orphan*/  tfm; scalar_t__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_ASYNC ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_alloc_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_hash (int /*<<< orphan*/ ) ; 
 int crypto_hash_init (struct hash_desc*) ; 
 int /*<<< orphan*/  ima_hash ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int init_desc(struct hash_desc *desc)
{
	int rc;

	desc->tfm = crypto_alloc_hash(ima_hash, 0, CRYPTO_ALG_ASYNC);
	if (IS_ERR(desc->tfm)) {
		pr_info("IMA: failed to load %s transform: %ld\n",
			ima_hash, PTR_ERR(desc->tfm));
		rc = PTR_ERR(desc->tfm);
		return rc;
	}
	desc->flags = 0;
	rc = crypto_hash_init(desc);
	if (rc)
		crypto_free_hash(desc->tfm);
	return rc;
}