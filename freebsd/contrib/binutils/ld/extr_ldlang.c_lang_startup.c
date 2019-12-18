#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char const* filename; char const* local_sym_name; int /*<<< orphan*/  real; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  einfo (int /*<<< orphan*/ ) ; 
 TYPE_1__* first_file ; 
 char const* startup_file ; 

void
lang_startup (const char *name)
{
  if (startup_file != NULL)
    {
      einfo (_("%P%F: multiple STARTUP files\n"));
    }
  first_file->filename = name;
  first_file->local_sym_name = name;
  first_file->real = TRUE;

  startup_file = name;
}