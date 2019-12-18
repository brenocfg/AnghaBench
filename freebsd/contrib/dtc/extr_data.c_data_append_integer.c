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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_fdt16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_fdt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_fdt64 (int /*<<< orphan*/ ) ; 
 struct data data_append_data (struct data,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  die (char*,int) ; 

struct data data_append_integer(struct data d, uint64_t value, int bits)
{
	uint8_t value_8;
	uint16_t value_16;
	uint32_t value_32;
	uint64_t value_64;

	switch (bits) {
	case 8:
		value_8 = value;
		return data_append_data(d, &value_8, 1);

	case 16:
		value_16 = cpu_to_fdt16(value);
		return data_append_data(d, &value_16, 2);

	case 32:
		value_32 = cpu_to_fdt32(value);
		return data_append_data(d, &value_32, 4);

	case 64:
		value_64 = cpu_to_fdt64(value);
		return data_append_data(d, &value_64, 8);

	default:
		die("Invalid literal size (%d)\n", bits);
	}
}