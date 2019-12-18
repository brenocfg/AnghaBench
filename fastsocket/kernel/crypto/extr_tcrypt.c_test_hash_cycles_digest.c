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
struct scatterlist {int dummy; } ;
struct hash_desc {int dummy; } ;
typedef  scalar_t__ cycles_t ;

/* Variables and functions */
 int crypto_hash_digest (struct hash_desc*,struct scatterlist*,int,char*) ; 
 scalar_t__ get_cycles () ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  printk (char*,unsigned long,unsigned long) ; 

__attribute__((used)) static int test_hash_cycles_digest(struct hash_desc *desc,
				   struct scatterlist *sg, int blen, char *out)
{
	unsigned long cycles = 0;
	int i;
	int ret;

	local_bh_disable();
	local_irq_disable();

	/* Warm-up run. */
	for (i = 0; i < 4; i++) {
		ret = crypto_hash_digest(desc, sg, blen, out);
		if (ret)
			goto out;
	}

	/* The real thing. */
	for (i = 0; i < 8; i++) {
		cycles_t start, end;

		start = get_cycles();

		ret = crypto_hash_digest(desc, sg, blen, out);
		if (ret)
			goto out;

		end = get_cycles();

		cycles += end - start;
	}

out:
	local_irq_enable();
	local_bh_enable();

	if (ret)
		return ret;

	printk("%6lu cycles/operation, %4lu cycles/byte\n",
	       cycles / 8, cycles / (8 * blen));

	return 0;
}