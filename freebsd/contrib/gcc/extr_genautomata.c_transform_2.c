#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct regexp {int dummy; } ;
typedef  TYPE_1__* regexp_t ;
struct TYPE_15__ {int regexps_num; TYPE_1__** regexps; } ;
struct TYPE_14__ {int regexps_num; TYPE_1__** regexps; } ;
struct TYPE_13__ {scalar_t__ mode; int /*<<< orphan*/  pos; } ;
struct TYPE_12__ {int regexps_num; TYPE_1__** regexps; } ;

/* Variables and functions */
 TYPE_10__* REGEXP_ALLOF (TYPE_1__*) ; 
 TYPE_8__* REGEXP_ONEOF (TYPE_1__*) ; 
 TYPE_6__* REGEXP_SEQUENCE (TYPE_1__*) ; 
 void* copy_insn_regexp (TYPE_1__*) ; 
 TYPE_1__* create_node (int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int regexp_transformed_p ; 
 scalar_t__ rm_allof ; 
 scalar_t__ rm_oneof ; 
 scalar_t__ rm_sequence ; 

__attribute__((used)) static regexp_t
transform_2 (regexp_t regexp)
{
  if (regexp->mode == rm_sequence)
    {
      regexp_t sequence = NULL;
      regexp_t result;
      int sequence_index = 0;
      int i, j;

      for (i = 0; i < REGEXP_SEQUENCE (regexp)->regexps_num; i++)
	if (REGEXP_SEQUENCE (regexp)->regexps [i]->mode == rm_sequence)
	  {
	    sequence_index = i;
	    sequence = REGEXP_SEQUENCE (regexp)->regexps [i];
	    break;
	  }
      if (i < REGEXP_SEQUENCE (regexp)->regexps_num)
	{
	  gcc_assert (REGEXP_SEQUENCE (sequence)->regexps_num > 1
		      && REGEXP_SEQUENCE (regexp)->regexps_num > 1);
	  result = create_node (sizeof (struct regexp)
                                + sizeof (regexp_t)
				* (REGEXP_SEQUENCE (regexp)->regexps_num
                                   + REGEXP_SEQUENCE (sequence)->regexps_num
                                   - 2));
	  result->mode = rm_sequence;
	  result->pos = regexp->pos;
	  REGEXP_SEQUENCE (result)->regexps_num
            = (REGEXP_SEQUENCE (regexp)->regexps_num
               + REGEXP_SEQUENCE (sequence)->regexps_num - 1);
	  for (i = 0; i < REGEXP_SEQUENCE (regexp)->regexps_num; i++)
            if (i < sequence_index)
              REGEXP_SEQUENCE (result)->regexps [i]
                = copy_insn_regexp (REGEXP_SEQUENCE (regexp)->regexps [i]);
            else if (i > sequence_index)
              REGEXP_SEQUENCE (result)->regexps
                [i + REGEXP_SEQUENCE (sequence)->regexps_num - 1]
                = copy_insn_regexp (REGEXP_SEQUENCE (regexp)->regexps [i]);
            else
              for (j = 0; j < REGEXP_SEQUENCE (sequence)->regexps_num; j++)
                REGEXP_SEQUENCE (result)->regexps [i + j]
                  = copy_insn_regexp (REGEXP_SEQUENCE (sequence)->regexps [j]);
	  regexp_transformed_p = 1;
	  regexp = result;
	}
    }
  else if (regexp->mode == rm_allof)
    {
      regexp_t allof = NULL;
      regexp_t result;
      int allof_index = 0;
      int i, j;

      for (i = 0; i < REGEXP_ALLOF (regexp)->regexps_num; i++)
	if (REGEXP_ALLOF (regexp)->regexps [i]->mode == rm_allof)
	  {
	    allof_index = i;
	    allof = REGEXP_ALLOF (regexp)->regexps [i];
	    break;
	  }
      if (i < REGEXP_ALLOF (regexp)->regexps_num)
	{
	  gcc_assert (REGEXP_ALLOF (allof)->regexps_num > 1
		      && REGEXP_ALLOF (regexp)->regexps_num > 1);
	  result = create_node (sizeof (struct regexp)
                                + sizeof (regexp_t)
				* (REGEXP_ALLOF (regexp)->regexps_num
                                   + REGEXP_ALLOF (allof)->regexps_num - 2));
	  result->mode = rm_allof;
	  result->pos = regexp->pos;
	  REGEXP_ALLOF (result)->regexps_num
            = (REGEXP_ALLOF (regexp)->regexps_num
               + REGEXP_ALLOF (allof)->regexps_num - 1);
	  for (i = 0; i < REGEXP_ALLOF (regexp)->regexps_num; i++)
            if (i < allof_index)
              REGEXP_ALLOF (result)->regexps [i]
                = copy_insn_regexp (REGEXP_ALLOF (regexp)->regexps [i]);
            else if (i > allof_index)
              REGEXP_ALLOF (result)->regexps
                [i + REGEXP_ALLOF (allof)->regexps_num - 1]
                = copy_insn_regexp (REGEXP_ALLOF (regexp)->regexps [i]);
            else
              for (j = 0; j < REGEXP_ALLOF (allof)->regexps_num; j++)
                REGEXP_ALLOF (result)->regexps [i + j]
                  = copy_insn_regexp (REGEXP_ALLOF (allof)->regexps [j]);
	  regexp_transformed_p = 1;
	  regexp = result;
	}
    }
  else if (regexp->mode == rm_oneof)
    {
      regexp_t oneof = NULL;
      regexp_t result;
      int oneof_index = 0;
      int i, j;

      for (i = 0; i < REGEXP_ONEOF (regexp)->regexps_num; i++)
	if (REGEXP_ONEOF (regexp)->regexps [i]->mode == rm_oneof)
	  {
	    oneof_index = i;
	    oneof = REGEXP_ONEOF (regexp)->regexps [i];
	    break;
	  }
      if (i < REGEXP_ONEOF (regexp)->regexps_num)
	{
	  gcc_assert (REGEXP_ONEOF (oneof)->regexps_num > 1
		      && REGEXP_ONEOF (regexp)->regexps_num > 1);
	  result = create_node (sizeof (struct regexp)
				+ sizeof (regexp_t)
				* (REGEXP_ONEOF (regexp)->regexps_num
                                   + REGEXP_ONEOF (oneof)->regexps_num - 2));
	  result->mode = rm_oneof;
	  result->pos = regexp->pos;
	  REGEXP_ONEOF (result)->regexps_num
	    = (REGEXP_ONEOF (regexp)->regexps_num
               + REGEXP_ONEOF (oneof)->regexps_num - 1);
	  for (i = 0; i < REGEXP_ONEOF (regexp)->regexps_num; i++)
            if (i < oneof_index)
              REGEXP_ONEOF (result)->regexps [i]
                = copy_insn_regexp (REGEXP_ONEOF (regexp)->regexps [i]);
            else if (i > oneof_index)
              REGEXP_ONEOF (result)->regexps
                [i + REGEXP_ONEOF (oneof)->regexps_num - 1]
                = copy_insn_regexp (REGEXP_ONEOF (regexp)->regexps [i]);
            else
              for (j = 0; j < REGEXP_ONEOF (oneof)->regexps_num; j++)
                REGEXP_ONEOF (result)->regexps [i + j]
                  = copy_insn_regexp (REGEXP_ONEOF (oneof)->regexps [j]);
	  regexp_transformed_p = 1;
	  regexp = result;
	}
    }
  return regexp;
}