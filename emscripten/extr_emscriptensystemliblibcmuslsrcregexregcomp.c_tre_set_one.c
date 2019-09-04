#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int position; int code_min; int code_max; int backref; int /*<<< orphan*/ * neg_classes; int /*<<< orphan*/  class; } ;
typedef  TYPE_1__ tre_pos_and_tags_t ;
typedef  int /*<<< orphan*/  tre_mem_t ;
typedef  int /*<<< orphan*/  tre_ctype_t ;

/* Variables and functions */
 TYPE_1__* tre_mem_calloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static tre_pos_and_tags_t *
tre_set_one(tre_mem_t mem, int position, int code_min, int code_max,
	    tre_ctype_t class, tre_ctype_t *neg_classes, int backref)
{
  tre_pos_and_tags_t *new_set;

  new_set = tre_mem_calloc(mem, sizeof(*new_set) * 2);
  if (new_set == NULL)
    return NULL;

  new_set[0].position = position;
  new_set[0].code_min = code_min;
  new_set[0].code_max = code_max;
  new_set[0].class = class;
  new_set[0].neg_classes = neg_classes;
  new_set[0].backref = backref;
  new_set[1].position = -1;
  new_set[1].code_min = -1;
  new_set[1].code_max = -1;

  return new_set;
}