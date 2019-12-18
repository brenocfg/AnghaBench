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
struct elf32_arm_link_hash_table {int byteswap_code; } ;
struct bfd_link_info {int dummy; } ;

/* Variables and functions */
 struct elf32_arm_link_hash_table* elf32_arm_hash_table (struct bfd_link_info*) ; 

void
bfd_elf32_arm_set_byteswap_code (struct bfd_link_info *info,
				 int byteswap_code)
{
  struct elf32_arm_link_hash_table *globals;

  globals = elf32_arm_hash_table (info);
  globals->byteswap_code = byteswap_code;
}