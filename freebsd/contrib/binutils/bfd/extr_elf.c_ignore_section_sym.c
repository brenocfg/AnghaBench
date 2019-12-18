#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_7__ {int flags; scalar_t__ value; TYPE_2__* section; } ;
typedef  TYPE_3__ asymbol ;
struct TYPE_6__ {scalar_t__ output_offset; TYPE_1__* output_section; int /*<<< orphan*/ * owner; } ;
struct TYPE_5__ {int /*<<< orphan*/ * owner; } ;

/* Variables and functions */
 int BSF_SECTION_SYM ; 

__attribute__((used)) static bfd_boolean
ignore_section_sym (bfd *abfd, asymbol *sym)
{
  return ((sym->flags & BSF_SECTION_SYM) != 0
	  && (sym->value != 0
	      || (sym->section->owner != abfd
		  && (sym->section->output_section->owner != abfd
		      || sym->section->output_offset != 0))));
}