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
struct TYPE_4__ {int position; int code_min; int code_max; } ;
typedef  TYPE_1__ tre_pos_and_tags_t ;
typedef  int /*<<< orphan*/  tre_mem_t ;

/* Variables and functions */
 TYPE_1__* tre_mem_calloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static tre_pos_and_tags_t *
tre_set_empty(tre_mem_t mem)
{
  tre_pos_and_tags_t *new_set;

  new_set = tre_mem_calloc(mem, sizeof(*new_set));
  if (new_set == NULL)
    return NULL;

  new_set[0].position = -1;
  new_set[0].code_min = -1;
  new_set[0].code_max = -1;

  return new_set;
}