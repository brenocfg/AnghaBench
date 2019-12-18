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
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__* trainer_flags ; 
 scalar_t__* trainer_memory ; 

__attribute__((used)) static void trainer_search_unchanged(void)
{
	UWORD trainer_value = 0;
	int value_valid = get_hex(&trainer_value);

	if (trainer_memory != NULL) {
		long int count = 65535;
		do {
			if (value_valid) {
				if (trainer_value != MEMORY_SafeGetByte((UWORD) count)) {
					*(trainer_flags+count) = 0;
				}
			} else {
				if (*(trainer_memory+count) != MEMORY_SafeGetByte((UWORD) count)) {
					*(trainer_flags+count) = 0;
				}
			}
			*(trainer_memory+count) = MEMORY_SafeGetByte((UWORD) count);
		} while (--count > -1);
	} else {
		printf("Use tss first.\n");
	}
}