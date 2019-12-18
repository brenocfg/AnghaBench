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
struct shash_alg {int /*<<< orphan*/  digestsize; } ;
struct seq_file {int dummy; } ;
struct crypto_alg {int /*<<< orphan*/  cra_blocksize; } ;

/* Variables and functions */
 struct shash_alg* __crypto_shash_alg (struct crypto_alg*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static void crypto_shash_show(struct seq_file *m, struct crypto_alg *alg)
{
	struct shash_alg *salg = __crypto_shash_alg(alg);

	seq_printf(m, "type         : shash\n");
	seq_printf(m, "blocksize    : %u\n", alg->cra_blocksize);
	seq_printf(m, "digestsize   : %u\n", salg->digestsize);
}