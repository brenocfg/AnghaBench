#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_15__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_11__ ;

/* Type definitions */
struct regexp {int dummy; } ;
typedef  TYPE_2__* regexp_t ;
struct TYPE_23__ {TYPE_1__* reserv_decl; } ;
struct TYPE_22__ {int regexps_num; TYPE_2__** regexps; } ;
struct TYPE_21__ {int mode; } ;
struct TYPE_20__ {TYPE_2__* regexp; } ;
struct TYPE_19__ {int regexps_num; TYPE_2__** regexps; } ;
struct TYPE_18__ {int regexps_num; TYPE_2__** regexps; } ;
struct TYPE_17__ {TYPE_2__* regexp; } ;

/* Variables and functions */
 TYPE_15__* REGEXP_ALLOF (TYPE_2__*) ; 
 TYPE_13__* REGEXP_ONEOF (TYPE_2__*) ; 
 TYPE_11__* REGEXP_REPEAT (TYPE_2__*) ; 
 TYPE_9__* REGEXP_RESERV (TYPE_2__*) ; 
 TYPE_7__* REGEXP_SEQUENCE (TYPE_2__*) ; 
 TYPE_2__* copy_node (TYPE_2__*,int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
#define  rm_allof 134 
#define  rm_nothing 133 
#define  rm_oneof 132 
#define  rm_repeat 131 
#define  rm_reserv 130 
#define  rm_sequence 129 
#define  rm_unit 128 

__attribute__((used)) static regexp_t
copy_insn_regexp (regexp_t regexp)
{
  regexp_t  result;
  int i;

  switch (regexp->mode)
    {
    case rm_reserv:
      result = copy_insn_regexp (REGEXP_RESERV (regexp)->reserv_decl->regexp);
      break;

    case rm_unit:
      result = copy_node (regexp, sizeof (struct regexp));
      break;

    case rm_repeat:
      result = copy_node (regexp, sizeof (struct regexp));
      REGEXP_REPEAT (result)->regexp
        = copy_insn_regexp (REGEXP_REPEAT (regexp)->regexp);
      break;

    case rm_sequence:
      result = copy_node (regexp,
                          sizeof (struct regexp) + sizeof (regexp_t)
			  * (REGEXP_SEQUENCE (regexp)->regexps_num - 1));
      for (i = 0; i <REGEXP_SEQUENCE (regexp)->regexps_num; i++)
	REGEXP_SEQUENCE (result)->regexps [i]
	  = copy_insn_regexp (REGEXP_SEQUENCE (regexp)->regexps [i]);
      break;

    case rm_allof:
      result = copy_node (regexp,
                          sizeof (struct regexp) + sizeof (regexp_t)
			  * (REGEXP_ALLOF (regexp)->regexps_num - 1));
      for (i = 0; i < REGEXP_ALLOF (regexp)->regexps_num; i++)
	REGEXP_ALLOF (result)->regexps [i]
	  = copy_insn_regexp (REGEXP_ALLOF (regexp)->regexps [i]);
      break;

    case rm_oneof:
      result = copy_node (regexp,
                          sizeof (struct regexp) + sizeof (regexp_t)
			  * (REGEXP_ONEOF (regexp)->regexps_num - 1));
      for (i = 0; i < REGEXP_ONEOF (regexp)->regexps_num; i++)
	REGEXP_ONEOF (result)->regexps [i]
	  = copy_insn_regexp (REGEXP_ONEOF (regexp)->regexps [i]);
      break;

    case rm_nothing:
      result = copy_node (regexp, sizeof (struct regexp));
      break;

    default:
      gcc_unreachable ();
    }
  return result;
}