#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct action_record {int filter; int next; int offset; } ;
typedef  int /*<<< orphan*/  htab_t ;
struct TYPE_4__ {TYPE_1__* eh; } ;
struct TYPE_3__ {int /*<<< orphan*/  action_record_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  INSERT ; 
 int VARRAY_ACTIVE_SIZE (int /*<<< orphan*/ ) ; 
 TYPE_2__* cfun ; 
 scalar_t__ htab_find_slot (int /*<<< orphan*/ ,struct action_record*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_sleb128 (int /*<<< orphan*/ *,int) ; 
 struct action_record* xmalloc (int) ; 

__attribute__((used)) static int
add_action_record (htab_t ar_hash, int filter, int next)
{
  struct action_record **slot, *new, tmp;

  tmp.filter = filter;
  tmp.next = next;
  slot = (struct action_record **) htab_find_slot (ar_hash, &tmp, INSERT);

  if ((new = *slot) == NULL)
    {
      new = xmalloc (sizeof (*new));
      new->offset = VARRAY_ACTIVE_SIZE (cfun->eh->action_record_data) + 1;
      new->filter = filter;
      new->next = next;
      *slot = new;

      /* The filter value goes in untouched.  The link to the next
	 record is a "self-relative" byte offset, or zero to indicate
	 that there is no next record.  So convert the absolute 1 based
	 indices we've been carrying around into a displacement.  */

      push_sleb128 (&cfun->eh->action_record_data, filter);
      if (next)
	next -= VARRAY_ACTIVE_SIZE (cfun->eh->action_record_data) + 1;
      push_sleb128 (&cfun->eh->action_record_data, next);
    }

  return new->offset;
}