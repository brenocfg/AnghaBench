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
typedef  int /*<<< orphan*/  bfd_vma ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  bfd_scan_vma (char*,char const**,int) ; 
 int /*<<< orphan*/  einfo (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exp_intop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lang_section_start (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
set_section_start (char *sect, char *valstr)
{
  const char *end;
  bfd_vma val = bfd_scan_vma (valstr, &end, 16);
  if (*end)
    einfo (_("%P%F: invalid hex number `%s'\n"), valstr);
  lang_section_start (sect, exp_intop (val), NULL);
}