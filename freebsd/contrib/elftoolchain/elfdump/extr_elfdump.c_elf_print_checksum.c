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
struct elfdump {int /*<<< orphan*/  elf; int /*<<< orphan*/  snl; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gelf_checksum (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
elf_print_checksum(struct elfdump *ed)
{

	if (!STAILQ_EMPTY(&ed->snl))
		return;

	PRT("\nelf checksum: %#lx\n", gelf_checksum(ed->elf));
}