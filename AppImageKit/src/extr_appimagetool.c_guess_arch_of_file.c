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
typedef  int /*<<< orphan*/  int16_t ;
typedef  int /*<<< orphan*/  gchar ;

/* Variables and functions */
 int /*<<< orphan*/  extract_arch_from_e_machine_field (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int*) ; 
 int /*<<< orphan*/  read_elf_e_machine_field (int /*<<< orphan*/  const*) ; 

void guess_arch_of_file(const gchar *archfile, bool* archs) {
    int16_t e_machine_field = read_elf_e_machine_field(archfile);
    extract_arch_from_e_machine_field(e_machine_field, archfile, archs);
}