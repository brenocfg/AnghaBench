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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct acpi_generic_address {scalar_t__ access_width; scalar_t__ bit_offset; void* bit_width; void* space_id; int /*<<< orphan*/  address; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_MOVE_64_TO_64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ACPI_MUL_8 (void*) ; 

__attribute__((used)) static inline void
acpi_tb_init_generic_address(struct acpi_generic_address *generic_address,
			     u8 space_id, u8 byte_width, u64 address)
{

	/*
	 * The 64-bit Address field is non-aligned in the byte packed
	 * GAS struct.
	 */
	ACPI_MOVE_64_TO_64(&generic_address->address, &address);

	/* All other fields are byte-wide */

	generic_address->space_id = space_id;
	generic_address->bit_width = (u8)ACPI_MUL_8(byte_width);
	generic_address->bit_offset = 0;
	generic_address->access_width = 0;	/* Access width ANY */
}