#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_13__ ;
typedef  struct TYPE_15__   TYPE_11__ ;

/* Type definitions */
typedef  TYPE_1__* regexp_t ;
struct TYPE_21__ {int repeat_num; TYPE_1__* regexp; } ;
struct TYPE_20__ {char* name; } ;
struct TYPE_19__ {int regexps_num; TYPE_1__** regexps; } ;
struct TYPE_18__ {char* name; } ;
struct TYPE_17__ {int mode; } ;
struct TYPE_16__ {int regexps_num; TYPE_1__** regexps; } ;
struct TYPE_15__ {int regexps_num; TYPE_1__** regexps; } ;

/* Variables and functions */
 char* NOTHING_NAME ; 
 TYPE_13__* REGEXP_ALLOF (TYPE_1__*) ; 
 TYPE_11__* REGEXP_ONEOF (TYPE_1__*) ; 
 TYPE_9__* REGEXP_REPEAT (TYPE_1__*) ; 
 TYPE_7__* REGEXP_RESERV (TYPE_1__*) ; 
 TYPE_5__* REGEXP_SEQUENCE (TYPE_1__*) ; 
 TYPE_3__* REGEXP_UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  irp ; 
 int /*<<< orphan*/  obstack_1grow (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  obstack_grow (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
#define  rm_allof 134 
#define  rm_nothing 133 
#define  rm_oneof 132 
#define  rm_repeat 131 
#define  rm_reserv 130 
#define  rm_sequence 129 
#define  rm_unit 128 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void
form_regexp (regexp_t regexp)
{
  int i;

  switch (regexp->mode)
    {
    case rm_unit: case rm_reserv:
      {
	const char *name = (regexp->mode == rm_unit
			    ? REGEXP_UNIT (regexp)->name
			    : REGEXP_RESERV (regexp)->name);
	
	obstack_grow (&irp, name, strlen (name));
	break;
      }
      
    case rm_sequence:
      for (i = 0; i < REGEXP_SEQUENCE (regexp)->regexps_num; i++)
	{
	  if (i != 0)
	    obstack_1grow (&irp, ',');
	  form_regexp (REGEXP_SEQUENCE (regexp)->regexps [i]);
	}
      break;

    case rm_allof:
      obstack_1grow (&irp, '(');
      for (i = 0; i < REGEXP_ALLOF (regexp)->regexps_num; i++)
	{
	  if (i != 0)
            obstack_1grow (&irp, '+');
	  if (REGEXP_ALLOF (regexp)->regexps[i]->mode == rm_sequence
              || REGEXP_ALLOF (regexp)->regexps[i]->mode == rm_oneof)
            obstack_1grow (&irp, '(');
	  form_regexp (REGEXP_ALLOF (regexp)->regexps [i]);
	  if (REGEXP_ALLOF (regexp)->regexps[i]->mode == rm_sequence
              || REGEXP_ALLOF (regexp)->regexps[i]->mode == rm_oneof)
            obstack_1grow (&irp, ')');
        }
      obstack_1grow (&irp, ')');
      break;
      
    case rm_oneof:
      for (i = 0; i < REGEXP_ONEOF (regexp)->regexps_num; i++)
	{
	  if (i != 0)
	    obstack_1grow (&irp, '|');
	  if (REGEXP_ONEOF (regexp)->regexps[i]->mode == rm_sequence)
	    obstack_1grow (&irp, '(');
	  form_regexp (REGEXP_ONEOF (regexp)->regexps [i]);
	  if (REGEXP_ONEOF (regexp)->regexps[i]->mode == rm_sequence)
          obstack_1grow (&irp, ')');
	}
      break;
      
    case rm_repeat:
      {
	char digits [30];
	
	if (REGEXP_REPEAT (regexp)->regexp->mode == rm_sequence
	    || REGEXP_REPEAT (regexp)->regexp->mode == rm_allof
	    || REGEXP_REPEAT (regexp)->regexp->mode == rm_oneof)
	  obstack_1grow (&irp, '(');
	form_regexp (REGEXP_REPEAT (regexp)->regexp);
	if (REGEXP_REPEAT (regexp)->regexp->mode == rm_sequence
	    || REGEXP_REPEAT (regexp)->regexp->mode == rm_allof
	    || REGEXP_REPEAT (regexp)->regexp->mode == rm_oneof)
	  obstack_1grow (&irp, ')');
	sprintf (digits, "*%d", REGEXP_REPEAT (regexp)->repeat_num);
	obstack_grow (&irp, digits, strlen (digits));
	break;
      }

    case rm_nothing:
      obstack_grow (&irp, NOTHING_NAME, strlen (NOTHING_NAME));
      break;

    default:
      gcc_unreachable ();
    }
}