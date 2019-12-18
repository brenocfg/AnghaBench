#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_21__ ;
typedef  struct TYPE_28__   TYPE_1__ ;
typedef  struct TYPE_27__   TYPE_19__ ;
typedef  struct TYPE_26__   TYPE_17__ ;
typedef  struct TYPE_25__   TYPE_15__ ;
typedef  struct TYPE_24__   TYPE_13__ ;
typedef  struct TYPE_23__   TYPE_11__ ;

/* Type definitions */
struct regexp {int dummy; } ;
typedef  TYPE_1__* regexp_t ;
typedef  TYPE_2__* decl_t ;
struct TYPE_32__ {int regexps_num; TYPE_1__** regexps; } ;
struct TYPE_31__ {int /*<<< orphan*/  name; TYPE_19__* unit_decl; } ;
struct TYPE_30__ {int /*<<< orphan*/  mode; } ;
struct TYPE_29__ {int reserv_is_used; } ;
struct TYPE_28__ {int mode; int /*<<< orphan*/  pos; } ;
struct TYPE_27__ {int unit_is_used; } ;
struct TYPE_26__ {int regexps_num; TYPE_1__** regexps; } ;
struct TYPE_25__ {int regexps_num; TYPE_1__** regexps; } ;
struct TYPE_24__ {TYPE_1__* regexp; } ;
struct TYPE_23__ {TYPE_21__* reserv_decl; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_21__* DECL_RESERV (TYPE_2__*) ; 
 TYPE_19__* DECL_UNIT (TYPE_2__*) ; 
 TYPE_17__* REGEXP_ALLOF (TYPE_1__*) ; 
 TYPE_15__* REGEXP_ONEOF (TYPE_1__*) ; 
 TYPE_13__* REGEXP_REPEAT (TYPE_1__*) ; 
 TYPE_11__* REGEXP_RESERV (TYPE_1__*) ; 
 TYPE_9__* REGEXP_SEQUENCE (TYPE_1__*) ; 
 TYPE_7__* REGEXP_UNIT (TYPE_1__*) ; 
 TYPE_1__* create_node (int) ; 
#define  dm_reserv 135 
#define  dm_unit 134 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* find_decl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
#define  rm_allof 133 
#define  rm_nothing 132 
#define  rm_oneof 131 
#define  rm_repeat 130 
 int rm_reserv ; 
#define  rm_sequence 129 
#define  rm_unit 128 

__attribute__((used)) static regexp_t
process_regexp (regexp_t regexp)
{
  decl_t decl_in_table;
  regexp_t new_regexp;
  int i;

  switch (regexp->mode)
    {
    case rm_unit:
      decl_in_table = find_decl (REGEXP_UNIT (regexp)->name);
      if (decl_in_table == NULL)
        error ("undeclared unit or reservation `%s'",
	       REGEXP_UNIT (regexp)->name);
      else
	switch (decl_in_table->mode)
	  {
	  case dm_unit:
	    DECL_UNIT (decl_in_table)->unit_is_used = 1;
	    REGEXP_UNIT (regexp)->unit_decl = DECL_UNIT (decl_in_table);
	    break;

	  case dm_reserv:
	    DECL_RESERV (decl_in_table)->reserv_is_used = 1;
	    new_regexp = create_node (sizeof (struct regexp));
	    new_regexp->mode = rm_reserv;
	    new_regexp->pos = regexp->pos;
	    REGEXP_RESERV (new_regexp)->name = REGEXP_UNIT (regexp)->name;
	    REGEXP_RESERV (new_regexp)->reserv_decl
	      = DECL_RESERV (decl_in_table);
	    regexp = new_regexp;
	    break;

	  default:
	    gcc_unreachable ();
	}
      break;
    case rm_sequence:
      for (i = 0; i <REGEXP_SEQUENCE (regexp)->regexps_num; i++)
	REGEXP_SEQUENCE (regexp)->regexps [i]
	  = process_regexp (REGEXP_SEQUENCE (regexp)->regexps [i]);
      break;
    case rm_allof:
      for (i = 0; i < REGEXP_ALLOF (regexp)->regexps_num; i++)
	REGEXP_ALLOF (regexp)->regexps [i]
	  = process_regexp (REGEXP_ALLOF (regexp)->regexps [i]);
      break;
    case rm_oneof:
      for (i = 0; i < REGEXP_ONEOF (regexp)->regexps_num; i++)
	REGEXP_ONEOF (regexp)->regexps [i]
	  = process_regexp (REGEXP_ONEOF (regexp)->regexps [i]);
      break;
    case rm_repeat:
      REGEXP_REPEAT (regexp)->regexp
	= process_regexp (REGEXP_REPEAT (regexp)->regexp);
      break;
    case rm_nothing:
      break;
    default:
      gcc_unreachable ();
    }
  return regexp;
}