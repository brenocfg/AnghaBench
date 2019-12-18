#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_16__ ;
typedef  struct TYPE_20__   TYPE_14__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
typedef  TYPE_1__* regexp_t ;
struct TYPE_22__ {int mode; } ;
struct TYPE_21__ {int regexps_num; TYPE_1__** regexps; } ;
struct TYPE_20__ {int regexps_num; TYPE_1__** regexps; } ;
struct TYPE_19__ {TYPE_1__* regexp; } ;
struct TYPE_18__ {int regexps_num; TYPE_1__** regexps; } ;

/* Variables and functions */
 TYPE_16__* REGEXP_ALLOF (TYPE_1__*) ; 
 TYPE_14__* REGEXP_ONEOF (TYPE_1__*) ; 
 TYPE_12__* REGEXP_REPEAT (TYPE_1__*) ; 
 TYPE_10__* REGEXP_SEQUENCE (TYPE_1__*) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
#define  rm_allof 133 
#define  rm_nothing 132 
#define  rm_oneof 131 
#define  rm_repeat 130 
#define  rm_sequence 129 
#define  rm_unit 128 
 TYPE_1__* stub1 (TYPE_1__*) ; 

__attribute__((used)) static regexp_t
regexp_transform_func (regexp_t regexp, regexp_t (*func) (regexp_t regexp))
{
  int i;

  switch (regexp->mode)
    {
    case rm_sequence:
      for (i = 0; i < REGEXP_SEQUENCE (regexp)->regexps_num; i++)
	REGEXP_SEQUENCE (regexp)->regexps [i]
	  = regexp_transform_func (REGEXP_SEQUENCE (regexp)->regexps [i],
				   func);
      break;

    case rm_allof:
      for (i = 0; i < REGEXP_ALLOF (regexp)->regexps_num; i++)
	REGEXP_ALLOF (regexp)->regexps [i]
	  = regexp_transform_func (REGEXP_ALLOF (regexp)->regexps [i], func);
      break;

    case rm_oneof:
      for (i = 0; i < REGEXP_ONEOF (regexp)->regexps_num; i++)
	REGEXP_ONEOF (regexp)->regexps [i]
	  = regexp_transform_func (REGEXP_ONEOF (regexp)->regexps [i], func);
      break;

    case rm_repeat:
      REGEXP_REPEAT (regexp)->regexp
	= regexp_transform_func (REGEXP_REPEAT (regexp)->regexp, func);
      break;

    case rm_nothing:
    case rm_unit:
      break;

    default:
      gcc_unreachable ();
    }
  return (*func) (regexp);
}