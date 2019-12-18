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
struct dx_entry {int /*<<< orphan*/  block; } ;
typedef  int ext4_lblk_t ;

/* Variables and functions */
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline ext4_lblk_t dx_get_block(struct dx_entry *entry)
{
	return le32_to_cpu(entry->block) & 0x00ffffff;
}