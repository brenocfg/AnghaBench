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
struct shash_desc {int /*<<< orphan*/  flags; } ;
struct hash_desc {int /*<<< orphan*/  flags; int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 struct shash_desc** crypto_hash_ctx (int /*<<< orphan*/ ) ; 
 int crypto_shash_init (struct shash_desc*) ; 

__attribute__((used)) static int shash_compat_init(struct hash_desc *hdesc)
{
	struct shash_desc **descp = crypto_hash_ctx(hdesc->tfm);
	struct shash_desc *desc = *descp;

	desc->flags = hdesc->flags;

	return crypto_shash_init(desc);
}