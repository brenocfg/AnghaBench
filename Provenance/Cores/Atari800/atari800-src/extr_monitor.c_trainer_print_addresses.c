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
typedef  scalar_t__ UWORD ;
typedef  scalar_t__ ULONG ;

/* Variables and functions */
 int get_hex (scalar_t__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__* trainer_flags ; 
 int /*<<< orphan*/ * trainer_memory ; 

__attribute__((used)) static void trainer_print_addresses(void)
{
	UWORD addr_count_max = 0;
	int addr_valid = get_hex(&addr_count_max);

	/* default print size is 8*8 adresses */
	if (!addr_valid) {
		addr_count_max = 64;
	}

	if (trainer_memory != NULL) {
		long int count = 0;
		ULONG addr_count = 0;
		int i = 0;
		do {
			if (*(trainer_flags+count) != 0) {
				printf("%04X ", (UWORD) count);
				addr_count++;
				if (++i == 8) {
					printf("\n");
					i = 0;
				};
			};
		} while ((++count < 65536) && (addr_count < addr_count_max));
	printf("\n");
	} else {
		printf("Use tss first.\n");
	}
}