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
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_2__ {int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  abs_output_section ; 
 int /*<<< orphan*/  lang_size_sections_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lang_statement_iteration ; 
 TYPE_1__ statement_list ; 

void
one_lang_size_sections_pass (bfd_boolean *relax, bfd_boolean check_regions)
{
  lang_statement_iteration++;
  lang_size_sections_1 (statement_list.head, abs_output_section,
			&statement_list.head, 0, 0, relax, check_regions);
}