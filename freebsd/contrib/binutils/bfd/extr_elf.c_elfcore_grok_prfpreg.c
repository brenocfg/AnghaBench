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
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  Elf_Internal_Note ;

/* Variables and functions */
 int /*<<< orphan*/  elfcore_make_note_pseudosection (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
elfcore_grok_prfpreg (bfd *abfd, Elf_Internal_Note *note)
{
  return elfcore_make_note_pseudosection (abfd, ".reg2", note);
}