#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ object_target; scalar_t__ target_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  einfo (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  exit (int) ; 
 TYPE_1__* pe_detail_list ; 
 TYPE_1__* pe_details ; 
 scalar_t__ strcmp (scalar_t__,char const*) ; 

void
pe_dll_id_target (const char *target)
{
  int i;

  for (i = 0; pe_detail_list[i].target_name; i++)
    if (strcmp (pe_detail_list[i].target_name, target) == 0
	|| strcmp (pe_detail_list[i].object_target, target) == 0)
      {
	pe_details = pe_detail_list + i;
	return;
      }
  einfo (_("%XUnsupported PEI architecture: %s\n"), target);
  exit (1);
}