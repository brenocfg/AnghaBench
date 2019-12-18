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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 scalar_t__ GENL_MAX_ID ; 
 scalar_t__ GENL_MIN_ID ; 
 scalar_t__ genl_family_find_byid (scalar_t__) ; 

__attribute__((used)) static inline u16 genl_generate_id(void)
{
	static u16 id_gen_idx;
	int overflowed = 0;

	do {
		if (id_gen_idx == 0)
			id_gen_idx = GENL_MIN_ID;

		if (++id_gen_idx > GENL_MAX_ID) {
			if (!overflowed) {
				overflowed = 1;
				id_gen_idx = 0;
				continue;
			} else
				return 0;
		}

	} while (genl_family_find_byid(id_gen_idx));

	return id_gen_idx;
}