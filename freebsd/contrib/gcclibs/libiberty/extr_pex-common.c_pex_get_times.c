#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pex_time {int dummy; } ;
struct pex_obj {int count; int /*<<< orphan*/ * time; int /*<<< orphan*/ * status; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct pex_time*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct pex_time*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pex_get_status_and_time (struct pex_obj*,int /*<<< orphan*/ ,char const**,int*) ; 

int
pex_get_times (struct pex_obj *obj, int count, struct pex_time *vector)
{
  if (obj->status == NULL)
    {
      const char *errmsg;
      int err;

      if (!pex_get_status_and_time (obj, 0, &errmsg, &err))
	return 0;
    }

  if (obj->time == NULL)
    return 0;

  if (count > obj->count)
    {
      memset (vector + obj->count, 0,
	      (count - obj->count) * sizeof (struct pex_time));
      count = obj->count;
    }

  memcpy (vector, obj->time, count * sizeof (struct pex_time));

  return 1;
}