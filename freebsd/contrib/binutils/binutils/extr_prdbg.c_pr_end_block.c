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
struct pr_handle {int indent; int /*<<< orphan*/  f; } ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  indent (struct pr_handle*) ; 
 int /*<<< orphan*/  print_vma (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
pr_end_block (void *p, bfd_vma addr)
{
  struct pr_handle *info = (struct pr_handle *) p;
  char ab[20];

  info->indent -= 2;

  indent (info);
  print_vma (addr, ab, TRUE, TRUE);
  fprintf (info->f, "} /* %s */\n", ab);

  return TRUE;
}