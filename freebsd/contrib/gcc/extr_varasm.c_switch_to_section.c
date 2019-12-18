#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_17__ {int flags; } ;
struct TYPE_16__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* callback ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_14__ {int /*<<< orphan*/  flags; } ;
struct TYPE_15__ {int /*<<< orphan*/  decl; TYPE_2__ common; int /*<<< orphan*/  name; } ;
struct TYPE_18__ {TYPE_5__ common; TYPE_4__ unnamed; TYPE_3__ named; } ;
typedef  TYPE_6__ section ;
struct TYPE_13__ {int /*<<< orphan*/  (* named_section ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_19__ {TYPE_1__ asm_out; } ;
struct TYPE_12__ {int /*<<< orphan*/  unlikely_text_section_name; } ;

/* Variables and functions */
 int SECTION_DECLARED ; 
 int SECTION_FORGET ; 
#define  SECTION_NAMED 130 
#define  SECTION_NOSWITCH 129 
 int SECTION_STYLE (TYPE_6__*) ; 
#define  SECTION_UNNAMED 128 
 int /*<<< orphan*/  UNLIKELY_EXECUTED_TEXT_SECTION_NAME ; 
 TYPE_10__* cfun ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 TYPE_6__* in_section ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 TYPE_7__ targetm ; 

void
switch_to_section (section *new_section)
{
  if (in_section == new_section)
    return;

  if (new_section->common.flags & SECTION_FORGET)
    in_section = NULL;
  else
    in_section = new_section;

  switch (SECTION_STYLE (new_section))
    {
    case SECTION_NAMED:
      if (cfun
	  && !cfun->unlikely_text_section_name
	  && strcmp (new_section->named.name,
		     UNLIKELY_EXECUTED_TEXT_SECTION_NAME) == 0)
	cfun->unlikely_text_section_name = UNLIKELY_EXECUTED_TEXT_SECTION_NAME;

      targetm.asm_out.named_section (new_section->named.name,
				     new_section->named.common.flags,
				     new_section->named.decl);
      break;

    case SECTION_UNNAMED:
      new_section->unnamed.callback (new_section->unnamed.data);
      break;

    case SECTION_NOSWITCH:
      gcc_unreachable ();
      break;
    }

  new_section->common.flags |= SECTION_DECLARED;
}