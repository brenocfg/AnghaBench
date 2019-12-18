#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  addend_exp; TYPE_2__* section; int /*<<< orphan*/ * name; TYPE_5__* howto; TYPE_1__* output_section; scalar_t__ output_offset; } ;
typedef  TYPE_3__ lang_reloc_statement_type ;
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd_size_type ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/ * name; } ;
struct TYPE_6__ {scalar_t__ vma; } ;

/* Variables and functions */
 int SECTION_NAME_MAP_LENGTH ; 
 scalar_t__ TO_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_reloc_size (TYPE_5__*) ; 
 int /*<<< orphan*/  exp_print_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_opb () ; 
 int /*<<< orphan*/  minfo (char*,int /*<<< orphan*/ *,...) ; 
 scalar_t__ print_dot ; 
 int /*<<< orphan*/  print_nl () ; 
 int /*<<< orphan*/  print_space () ; 

__attribute__((used)) static void
print_reloc_statement (lang_reloc_statement_type *reloc)
{
  int i;
  bfd_vma addr;
  bfd_size_type size;

  init_opb ();
  for (i = 0; i < SECTION_NAME_MAP_LENGTH; i++)
    print_space ();

  addr = reloc->output_offset;
  if (reloc->output_section != NULL)
    addr += reloc->output_section->vma;

  size = bfd_get_reloc_size (reloc->howto);

  minfo ("0x%V %W RELOC %s ", addr, size, reloc->howto->name);

  if (reloc->name != NULL)
    minfo ("%s+", reloc->name);
  else
    minfo ("%s+", reloc->section->name);

  exp_print_tree (reloc->addend_exp);

  print_nl ();

  print_dot = addr + TO_ADDR (size);
}