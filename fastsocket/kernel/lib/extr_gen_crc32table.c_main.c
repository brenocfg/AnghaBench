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
 int /*<<< orphan*/  BE_TABLE_SIZE ; 
 int CRC_BE_BITS ; 
 int CRC_LE_BITS ; 
 int /*<<< orphan*/  LE_TABLE_SIZE ; 
 int /*<<< orphan*/  crc32init_be () ; 
 int /*<<< orphan*/  crc32init_le () ; 
 int /*<<< orphan*/  crc32table_be ; 
 int /*<<< orphan*/  crc32table_le ; 
 int /*<<< orphan*/  output_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 

int main(int argc, char** argv)
{
	printf("/* this file is generated - do not edit */\n\n");

	if (CRC_LE_BITS > 1) {
		crc32init_le();
		printf("static const u32 crc32table_le[] = {");
		output_table(crc32table_le, LE_TABLE_SIZE, "tole");
		printf("};\n");
	}

	if (CRC_BE_BITS > 1) {
		crc32init_be();
		printf("static const u32 crc32table_be[] = {");
		output_table(crc32table_be, BE_TABLE_SIZE, "tobe");
		printf("};\n");
	}

	return 0;
}