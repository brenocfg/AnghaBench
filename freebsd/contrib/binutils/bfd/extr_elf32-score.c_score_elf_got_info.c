#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct score_got_info {int dummy; } ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_3__ {struct score_got_info* got_info; } ;
struct TYPE_4__ {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * elf_section_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * score_elf_got_section (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* score_elf_section_data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct score_got_info *
score_elf_got_info (bfd *abfd, asection **sgotp)
{
  asection *sgot;
  struct score_got_info *g;

  sgot = score_elf_got_section (abfd, TRUE);
  BFD_ASSERT (sgot != NULL);
  BFD_ASSERT (elf_section_data (sgot) != NULL);
  g = score_elf_section_data (sgot)->u.got_info;
  BFD_ASSERT (g != NULL);

  if (sgotp)
    *sgotp = sgot;
  return g;
}