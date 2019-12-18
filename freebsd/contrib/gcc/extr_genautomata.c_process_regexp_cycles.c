#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_15__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_11__ ;

/* Type definitions */
typedef  TYPE_3__* regexp_t ;
struct TYPE_25__ {TYPE_2__* reserv_decl; } ;
struct TYPE_24__ {int regexps_num; TYPE_3__** regexps; } ;
struct TYPE_23__ {TYPE_1__* unit_decl; } ;
struct TYPE_22__ {int mode; } ;
struct TYPE_21__ {TYPE_3__* regexp; } ;
struct TYPE_20__ {int max_occ_cycle_num; int min_occ_cycle_num; } ;
struct TYPE_19__ {int regexps_num; TYPE_3__** regexps; } ;
struct TYPE_18__ {int regexps_num; TYPE_3__** regexps; } ;
struct TYPE_17__ {int repeat_num; TYPE_3__* regexp; } ;

/* Variables and functions */
 TYPE_15__* REGEXP_ALLOF (TYPE_3__*) ; 
 TYPE_13__* REGEXP_ONEOF (TYPE_3__*) ; 
 TYPE_11__* REGEXP_REPEAT (TYPE_3__*) ; 
 TYPE_9__* REGEXP_RESERV (TYPE_3__*) ; 
 TYPE_7__* REGEXP_SEQUENCE (TYPE_3__*) ; 
 TYPE_5__* REGEXP_UNIT (TYPE_3__*) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
#define  rm_allof 134 
#define  rm_nothing 133 
#define  rm_oneof 132 
#define  rm_repeat 131 
#define  rm_reserv 130 
#define  rm_sequence 129 
#define  rm_unit 128 

__attribute__((used)) static void
process_regexp_cycles (regexp_t regexp, int max_start_cycle,
		       int min_start_cycle, int *max_finish_cycle,
		       int *min_finish_cycle)
{
  int i;

  switch (regexp->mode)
    {
    case rm_unit:
      if (REGEXP_UNIT (regexp)->unit_decl->max_occ_cycle_num < max_start_cycle)
	REGEXP_UNIT (regexp)->unit_decl->max_occ_cycle_num = max_start_cycle;
      if (REGEXP_UNIT (regexp)->unit_decl->min_occ_cycle_num > min_start_cycle
	  || REGEXP_UNIT (regexp)->unit_decl->min_occ_cycle_num == -1)
	REGEXP_UNIT (regexp)->unit_decl->min_occ_cycle_num = min_start_cycle;
      *max_finish_cycle = max_start_cycle;
      *min_finish_cycle = min_start_cycle;
      break;

    case rm_reserv:
      process_regexp_cycles (REGEXP_RESERV (regexp)->reserv_decl->regexp,
			     max_start_cycle, min_start_cycle,
			     max_finish_cycle, min_finish_cycle);
      break;

    case rm_repeat:
      for (i = 0; i < REGEXP_REPEAT (regexp)->repeat_num; i++)
	{
	  process_regexp_cycles (REGEXP_REPEAT (regexp)->regexp,
				 max_start_cycle, min_start_cycle,
				 max_finish_cycle, min_finish_cycle);
	  max_start_cycle = *max_finish_cycle + 1;
	  min_start_cycle = *min_finish_cycle + 1;
	}
      break;

    case rm_sequence:
      for (i = 0; i <REGEXP_SEQUENCE (regexp)->regexps_num; i++)
	{
	  process_regexp_cycles (REGEXP_SEQUENCE (regexp)->regexps [i],
				 max_start_cycle, min_start_cycle,
				 max_finish_cycle, min_finish_cycle);
	  max_start_cycle = *max_finish_cycle + 1;
	  min_start_cycle = *min_finish_cycle + 1;
	}
      break;

    case rm_allof:
      {
	int max_cycle = 0;
	int min_cycle = 0;
	
	for (i = 0; i < REGEXP_ALLOF (regexp)->regexps_num; i++)
	  {
	    process_regexp_cycles (REGEXP_ALLOF (regexp)->regexps [i],
				   max_start_cycle, min_start_cycle,
				   max_finish_cycle, min_finish_cycle);
	    if (max_cycle < *max_finish_cycle)
	      max_cycle = *max_finish_cycle;
	    if (i == 0 || min_cycle > *min_finish_cycle)
	      min_cycle = *min_finish_cycle;
	  }
	*max_finish_cycle = max_cycle;
	*min_finish_cycle = min_cycle;
      }
      break;

    case rm_oneof:
      {
	int max_cycle = 0;
	int min_cycle = 0;
	
	for (i = 0; i < REGEXP_ONEOF (regexp)->regexps_num; i++)
	  {
	    process_regexp_cycles (REGEXP_ONEOF (regexp)->regexps [i],
				   max_start_cycle, min_start_cycle,
				   max_finish_cycle, min_finish_cycle);
	    if (max_cycle < *max_finish_cycle)
	      max_cycle = *max_finish_cycle;
	    if (i == 0 || min_cycle > *min_finish_cycle)
	      min_cycle = *min_finish_cycle;
	  }
	*max_finish_cycle = max_cycle;
	*min_finish_cycle = min_cycle;
      }
      break;

    case rm_nothing:
      *max_finish_cycle = max_start_cycle;
      *min_finish_cycle = min_start_cycle;
      break;

    default:
      gcc_unreachable ();
    }
}