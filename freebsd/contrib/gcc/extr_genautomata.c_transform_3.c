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
struct TYPE_13__ {int mode; int /*<<< orphan*/  pos; } ;
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
#define  rm_nothing 130 
 scalar_t__ rm_oneof ; 
#define  rm_sequence 129 
#define  rm_unit 128 

__attribute__((used)) static regexp_t
transform_3 (regexp_t regexp)
{
  if (regexp->mode == rm_sequence)
    {
      regexp_t oneof = NULL;
      int oneof_index = 0;
      regexp_t result;
      regexp_t sequence;
      int i, j;

      for (i = 0; i <REGEXP_SEQUENCE (regexp)->regexps_num; i++)
	if (REGEXP_SEQUENCE (regexp)->regexps [i]->mode == rm_oneof)
	  {
	    oneof_index = i;
	    oneof = REGEXP_SEQUENCE (regexp)->regexps [i];
	    break;
	  }
      if (i < REGEXP_SEQUENCE (regexp)->regexps_num)
	{
	  gcc_assert (REGEXP_ONEOF (oneof)->regexps_num > 1
		      && REGEXP_SEQUENCE (regexp)->regexps_num > 1);
	  result = create_node (sizeof (struct regexp)
				+ sizeof (regexp_t)
				* (REGEXP_ONEOF (oneof)->regexps_num - 1));
	  result->mode = rm_oneof;
	  result->pos = regexp->pos;
	  REGEXP_ONEOF (result)->regexps_num
	    = REGEXP_ONEOF (oneof)->regexps_num;
	  for (i = 0; i < REGEXP_ONEOF (result)->regexps_num; i++)
	    {
	      sequence
                = create_node (sizeof (struct regexp)
                               + sizeof (regexp_t)
                               * (REGEXP_SEQUENCE (regexp)->regexps_num - 1));
	      sequence->mode = rm_sequence;
	      sequence->pos = regexp->pos;
	      REGEXP_SEQUENCE (sequence)->regexps_num
                = REGEXP_SEQUENCE (regexp)->regexps_num;
              REGEXP_ONEOF (result)->regexps [i] = sequence;
	      for (j = 0; j < REGEXP_SEQUENCE (sequence)->regexps_num; j++)
		if (j != oneof_index)
		  REGEXP_SEQUENCE (sequence)->regexps [j]
		    = copy_insn_regexp (REGEXP_SEQUENCE (regexp)->regexps [j]);
		else
		  REGEXP_SEQUENCE (sequence)->regexps [j]
		    = copy_insn_regexp (REGEXP_ONEOF (oneof)->regexps [i]);
	    }
	  regexp_transformed_p = 1;
	  regexp = result;
	}
    }
  else if (regexp->mode == rm_allof)
    {
      regexp_t oneof = NULL;
      regexp_t seq;
      int oneof_index = 0;
      int max_seq_length, allof_length;
      regexp_t result;
      regexp_t allof = NULL;
      regexp_t allof_op = NULL;
      int i, j;

      for (i = 0; i < REGEXP_ALLOF (regexp)->regexps_num; i++)
	if (REGEXP_ALLOF (regexp)->regexps [i]->mode == rm_oneof)
	  {
	    oneof_index = i;
	    oneof = REGEXP_ALLOF (regexp)->regexps [i];
	    break;
	  }
      if (i < REGEXP_ALLOF (regexp)->regexps_num)
	{
	  gcc_assert (REGEXP_ONEOF (oneof)->regexps_num > 1
		      && REGEXP_ALLOF (regexp)->regexps_num > 1);
	  result = create_node (sizeof (struct regexp)
				+ sizeof (regexp_t)
				* (REGEXP_ONEOF (oneof)->regexps_num - 1));
	  result->mode = rm_oneof;
	  result->pos = regexp->pos;
	  REGEXP_ONEOF (result)->regexps_num
	    = REGEXP_ONEOF (oneof)->regexps_num;
	  for (i = 0; i < REGEXP_ONEOF (result)->regexps_num; i++)
	    {
	      allof
		= create_node (sizeof (struct regexp)
                               + sizeof (regexp_t)
			       * (REGEXP_ALLOF (regexp)->regexps_num - 1));
	      allof->mode = rm_allof;
	      allof->pos = regexp->pos;
	      REGEXP_ALLOF (allof)->regexps_num
                = REGEXP_ALLOF (regexp)->regexps_num;
              REGEXP_ONEOF (result)->regexps [i] = allof;
	      for (j = 0; j < REGEXP_ALLOF (allof)->regexps_num; j++)
		if (j != oneof_index)
		  REGEXP_ALLOF (allof)->regexps [j]
		    = copy_insn_regexp (REGEXP_ALLOF (regexp)->regexps [j]);
		else
		  REGEXP_ALLOF (allof)->regexps [j]
		    = copy_insn_regexp (REGEXP_ONEOF (oneof)->regexps [i]);
	    }
	  regexp_transformed_p = 1;
	  regexp = result;
	}
      max_seq_length = 0;
      if (regexp->mode == rm_allof)
	for (i = 0; i < REGEXP_ALLOF (regexp)->regexps_num; i++)
	  {
	    switch (REGEXP_ALLOF (regexp)->regexps [i]->mode)
	      {
	      case rm_sequence:
		seq = REGEXP_ALLOF (regexp)->regexps [i];
		if (max_seq_length < REGEXP_SEQUENCE (seq)->regexps_num)
		  max_seq_length = REGEXP_SEQUENCE (seq)->regexps_num;
		break;

	      case rm_unit:
	      case rm_nothing:
		break;

	      default:
		max_seq_length = 0;
		goto break_for;
	      }
	  }
    break_for:
      if (max_seq_length != 0)
	{
	  gcc_assert (max_seq_length != 1
		      && REGEXP_ALLOF (regexp)->regexps_num > 1);
	  result = create_node (sizeof (struct regexp)
				+ sizeof (regexp_t) * (max_seq_length - 1));
	  result->mode = rm_sequence;
	  result->pos = regexp->pos;
	  REGEXP_SEQUENCE (result)->regexps_num = max_seq_length;
	  for (i = 0; i < max_seq_length; i++)
	    {
	      allof_length = 0;
	      for (j = 0; j < REGEXP_ALLOF (regexp)->regexps_num; j++)
		switch (REGEXP_ALLOF (regexp)->regexps [j]->mode)
		  {
		  case rm_sequence:
		    if (i < (REGEXP_SEQUENCE (REGEXP_ALLOF (regexp)
					      ->regexps [j])->regexps_num))
		      {
			allof_op
			  = (REGEXP_SEQUENCE (REGEXP_ALLOF (regexp)
					      ->regexps [j])
			     ->regexps [i]);
			allof_length++;
		      }
		    break;
		  case rm_unit:
		  case rm_nothing:
		    if (i == 0)
		      {
			allof_op = REGEXP_ALLOF (regexp)->regexps [j];
			allof_length++;
		      }
		    break;
		  default:
		    break;
		  }
	      
	      if (allof_length == 1)
		REGEXP_SEQUENCE (result)->regexps [i] = allof_op;
	      else
		{
		  allof = create_node (sizeof (struct regexp)
				       + sizeof (regexp_t)
				       * (allof_length - 1));
		  allof->mode = rm_allof;
		  allof->pos = regexp->pos;
		  REGEXP_ALLOF (allof)->regexps_num = allof_length;
		  REGEXP_SEQUENCE (result)->regexps [i] = allof;
		  allof_length = 0;
		  for (j = 0; j < REGEXP_ALLOF (regexp)->regexps_num; j++)
		    if (REGEXP_ALLOF (regexp)->regexps [j]->mode == rm_sequence
			&& (i <
			    (REGEXP_SEQUENCE (REGEXP_ALLOF (regexp)
					      ->regexps [j])->regexps_num)))
		      {
			allof_op = (REGEXP_SEQUENCE (REGEXP_ALLOF (regexp)
						     ->regexps [j])
				    ->regexps [i]);
			REGEXP_ALLOF (allof)->regexps [allof_length]
			  = allof_op;
			allof_length++;
		      }
		    else if (i == 0
			     && (REGEXP_ALLOF (regexp)->regexps [j]->mode
				 == rm_unit
				 || (REGEXP_ALLOF (regexp)->regexps [j]->mode
				     == rm_nothing)))
		      {
			allof_op = REGEXP_ALLOF (regexp)->regexps [j];
			REGEXP_ALLOF (allof)->regexps [allof_length]
			  = allof_op;
			allof_length++;
		      }
		}
	    }
	  regexp_transformed_p = 1;
	  regexp = result;
	}
    }
  return regexp;
}