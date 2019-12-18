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
struct fw_card {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int BANDWIDTH_AVAILABLE_INITIAL ; 
 scalar_t__ CSR_BANDWIDTH_AVAILABLE ; 
 scalar_t__ CSR_REGISTER_BASE ; 
 int EAGAIN ; 
 int EIO ; 
#define  RCODE_COMPLETE 129 
#define  RCODE_GENERATION 128 
 int /*<<< orphan*/  SCODE_100 ; 
 int /*<<< orphan*/  TCODE_LOCK_COMPARE_SWAP ; 
 int be32_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int fw_run_transaction (struct fw_card*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int manage_bandwidth(struct fw_card *card, int irm_id, int generation,
			    int bandwidth, bool allocate, __be32 data[2])
{
	int try, new, old = allocate ? BANDWIDTH_AVAILABLE_INITIAL : 0;

	/*
	 * On a 1394a IRM with low contention, try < 1 is enough.
	 * On a 1394-1995 IRM, we need at least try < 2.
	 * Let's just do try < 5.
	 */
	for (try = 0; try < 5; try++) {
		new = allocate ? old - bandwidth : old + bandwidth;
		if (new < 0 || new > BANDWIDTH_AVAILABLE_INITIAL)
			break;

		data[0] = cpu_to_be32(old);
		data[1] = cpu_to_be32(new);
		switch (fw_run_transaction(card, TCODE_LOCK_COMPARE_SWAP,
				irm_id, generation, SCODE_100,
				CSR_REGISTER_BASE + CSR_BANDWIDTH_AVAILABLE,
				data, 8)) {
		case RCODE_GENERATION:
			/* A generation change frees all bandwidth. */
			return allocate ? -EAGAIN : bandwidth;

		case RCODE_COMPLETE:
			if (be32_to_cpup(data) == old)
				return bandwidth;

			old = be32_to_cpup(data);
			/* Fall through. */
		}
	}

	return -EIO;
}