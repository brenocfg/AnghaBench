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

/* Variables and functions */
 int /*<<< orphan*/  NS_ERR (char*,...) ; 
 int /*<<< orphan*/  NS_INFO (char*,...) ; 
 int* erase_block_wear ; 
 scalar_t__ rptwear ; 
 scalar_t__ rptwear_cnt ; 
 scalar_t__ total_wear ; 
 unsigned int wear_eb_count ; 

__attribute__((used)) static void update_wear(unsigned int erase_block_no)
{
	unsigned long wmin = -1, wmax = 0, avg;
	unsigned long deciles[10], decile_max[10], tot = 0;
	unsigned int i;

	if (!erase_block_wear)
		return;
	total_wear += 1;
	if (total_wear == 0)
		NS_ERR("Erase counter total overflow\n");
	erase_block_wear[erase_block_no] += 1;
	if (erase_block_wear[erase_block_no] == 0)
		NS_ERR("Erase counter overflow for erase block %u\n", erase_block_no);
	rptwear_cnt += 1;
	if (rptwear_cnt < rptwear)
		return;
	rptwear_cnt = 0;
	/* Calc wear stats */
	for (i = 0; i < wear_eb_count; ++i) {
		unsigned long wear = erase_block_wear[i];
		if (wear < wmin)
			wmin = wear;
		if (wear > wmax)
			wmax = wear;
		tot += wear;
	}
	for (i = 0; i < 9; ++i) {
		deciles[i] = 0;
		decile_max[i] = (wmax * (i + 1) + 5) / 10;
	}
	deciles[9] = 0;
	decile_max[9] = wmax;
	for (i = 0; i < wear_eb_count; ++i) {
		int d;
		unsigned long wear = erase_block_wear[i];
		for (d = 0; d < 10; ++d)
			if (wear <= decile_max[d]) {
				deciles[d] += 1;
				break;
			}
	}
	avg = tot / wear_eb_count;
	/* Output wear report */
	NS_INFO("*** Wear Report ***\n");
	NS_INFO("Total numbers of erases:  %lu\n", tot);
	NS_INFO("Number of erase blocks:   %u\n", wear_eb_count);
	NS_INFO("Average number of erases: %lu\n", avg);
	NS_INFO("Maximum number of erases: %lu\n", wmax);
	NS_INFO("Minimum number of erases: %lu\n", wmin);
	for (i = 0; i < 10; ++i) {
		unsigned long from = (i ? decile_max[i - 1] + 1 : 0);
		if (from > decile_max[i])
			continue;
		NS_INFO("Number of ebs with erase counts from %lu to %lu : %lu\n",
			from,
			decile_max[i],
			deciles[i]);
	}
	NS_INFO("*** End of Wear Report ***\n");
}