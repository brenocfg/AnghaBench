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

/* Variables and functions */
 scalar_t__ MEMORY_SafeGetByte (scalar_t__) ; 
 int get_hex (scalar_t__*) ; 
 scalar_t__* malloc (int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int* trainer_flags ; 
 scalar_t__* trainer_memory ; 

__attribute__((used)) static void trainer_start_search(void)
{
	UWORD trainer_value = 0;
	int value_valid = get_hex(&trainer_value);

	/* alloc needed memory at first use */
	if (trainer_memory == NULL) {
		trainer_memory = malloc(65536*2);
		if (trainer_memory != NULL) {
			trainer_flags = trainer_memory + 65536;
		} else {
			printf("Memory allocation failed!\n"
			"Trainer not available.\n");
		}
	}
	if (trainer_memory != NULL) {
		/* copy memory into shadow buffer at first use */
		long int count = 65535;
		do {
			*(trainer_memory+count) = MEMORY_SafeGetByte((UWORD) count);
			*(trainer_flags+count) = 0xff;
		} while (--count > -1);
		if (value_valid) {
			count = 65535;
			do {
				if (trainer_value != *(trainer_memory+count)) {
					*(trainer_flags+count) = 0;
				}
			} while (--count > -1);
		}
	}
}