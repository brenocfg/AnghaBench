#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  target; } ;
struct TYPE_12__ {int /*<<< orphan*/  name; } ;
struct TYPE_11__ {int type; } ;
struct TYPE_13__ {TYPE_1__ target_statement; TYPE_3__ output_statement; TYPE_2__ header; } ;
typedef  TYPE_4__ lang_statement_union_type ;
struct TYPE_16__ {int /*<<< orphan*/  text_read_only; int /*<<< orphan*/  magic_demand_paged; } ;
struct TYPE_15__ {int /*<<< orphan*/  traditional_format; int /*<<< orphan*/  relocatable; } ;
struct TYPE_14__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BFD_TRADITIONAL_FORMAT ; 
 int /*<<< orphan*/  D_PAGED ; 
 int /*<<< orphan*/  WP_TEXT ; 
 TYPE_9__ config ; 
 int /*<<< orphan*/  current_target ; 
#define  lang_output_statement_enum 129 
#define  lang_target_statement_enum 128 
 int /*<<< orphan*/  ldemul_set_output_arch () ; 
 TYPE_7__ link_info ; 
 TYPE_5__* open_output (int /*<<< orphan*/ ) ; 
 TYPE_5__* output_bfd ; 

__attribute__((used)) static void
ldlang_open_output (lang_statement_union_type *statement)
{
  switch (statement->header.type)
    {
    case lang_output_statement_enum:
      ASSERT (output_bfd == NULL);
      output_bfd = open_output (statement->output_statement.name);
      ldemul_set_output_arch ();
      if (config.magic_demand_paged && !link_info.relocatable)
	output_bfd->flags |= D_PAGED;
      else
	output_bfd->flags &= ~D_PAGED;
      if (config.text_read_only)
	output_bfd->flags |= WP_TEXT;
      else
	output_bfd->flags &= ~WP_TEXT;
      if (link_info.traditional_format)
	output_bfd->flags |= BFD_TRADITIONAL_FORMAT;
      else
	output_bfd->flags &= ~BFD_TRADITIONAL_FORMAT;
      break;

    case lang_target_statement_enum:
      current_target = statement->target_statement.target;
      break;
    default:
      break;
    }
}