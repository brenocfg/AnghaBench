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
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  einfo (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  lang_add_output_format (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 

void
mri_format (const char *name)
{
  if (strcmp (name, "S") == 0)
    lang_add_output_format ("srec", NULL, NULL, 1);

  else if (strcmp (name, "IEEE") == 0)
    lang_add_output_format ("ieee", NULL, NULL, 1);

  else if (strcmp (name, "COFF") == 0)
    lang_add_output_format ("coff-m68k", NULL, NULL, 1);

  else
    einfo (_("%P%F: unknown format type %s\n"), name);
}