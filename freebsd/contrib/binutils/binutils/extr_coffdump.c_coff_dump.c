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
struct coff_ofile {int nsources; int nsections; scalar_t__ sections; int /*<<< orphan*/  source_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  dump_coff_section (scalar_t__) ; 
 int /*<<< orphan*/  dump_coff_sfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nl () ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
coff_dump (struct coff_ofile *ptr)
{
  int i;

  printf ("Coff dump");
  nl ();
  printf ("#souces %d", ptr->nsources);
  nl ();
  dump_coff_sfile (ptr->source_head);

  for (i = 0; i < ptr->nsections; i++)
    dump_coff_section (ptr->sections + i);
}