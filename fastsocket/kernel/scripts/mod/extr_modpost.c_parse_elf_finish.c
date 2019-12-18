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
struct elf_info {int /*<<< orphan*/  size; int /*<<< orphan*/  hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  release_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parse_elf_finish(struct elf_info *info)
{
	release_file(info->hdr, info->size);
}