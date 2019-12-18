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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct fw_card {int dummy; } ;
typedef  int __be32 ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
#define  RCODE_COMPLETE 129 
#define  RCODE_GENERATION 128 
 int /*<<< orphan*/  SCODE_100 ; 
 int /*<<< orphan*/  TCODE_LOCK_COMPARE_SWAP ; 
 int cpu_to_be32 (int) ; 
 int fw_run_transaction (struct fw_card*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int manage_channel(struct fw_card *card, int irm_id, int generation,
		u32 channels_mask, u64 offset, bool allocate, __be32 data[2])
{
	__be32 c, all, old;
	int i, retry = 5;

	old = all = allocate ? cpu_to_be32(~0) : 0;

	for (i = 0; i < 32; i++) {
		if (!(channels_mask & 1 << i))
			continue;

		c = cpu_to_be32(1 << (31 - i));
		if ((old & c) != (all & c))
			continue;

		data[0] = old;
		data[1] = old ^ c;
		switch (fw_run_transaction(card, TCODE_LOCK_COMPARE_SWAP,
					   irm_id, generation, SCODE_100,
					   offset, data, 8)) {
		case RCODE_GENERATION:
			/* A generation change frees all channels. */
			return allocate ? -EAGAIN : i;

		case RCODE_COMPLETE:
			if (data[0] == old)
				return i;

			old = data[0];

			/* Is the IRM 1394a-2000 compliant? */
			if ((data[0] & c) == (data[1] & c))
				continue;

			/* 1394-1995 IRM, fall through to retry. */
		default:
			if (retry--)
				i--;
		}
	}

	return -EIO;
}