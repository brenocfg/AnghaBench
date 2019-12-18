#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct regexp {int dummy; } ;
typedef  TYPE_1__* regexp_t ;
struct TYPE_8__ {int regexps_num; TYPE_1__** regexps; } ;
struct TYPE_7__ {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 TYPE_5__* REGEXP_SEQUENCE (TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* create_node (int) ; 
 TYPE_1__* gen_regexp_oneof (char const*) ; 
 char** get_str_vect (char const*,int*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rm_sequence ; 

__attribute__((used)) static regexp_t
gen_regexp_sequence (const char *str)
{
  regexp_t sequence;
  char **sequence_vect;
  int els_num;
  int i;

  sequence_vect = get_str_vect (str, &els_num, ',', TRUE);
  if (els_num > 1)
    {
      sequence = create_node (sizeof (struct regexp)
			      + sizeof (regexp_t) * (els_num - 1));
      sequence->mode = rm_sequence;
      REGEXP_SEQUENCE (sequence)->regexps_num = els_num;
      for (i = 0; i < els_num; i++)
	REGEXP_SEQUENCE (sequence)->regexps [i]
          = gen_regexp_oneof (sequence_vect [i]);
      return sequence;
    }
  else
    return gen_regexp_oneof (str);
}