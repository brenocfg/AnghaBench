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
struct id {scalar_t__ sequence; struct id* next; int /*<<< orphan*/  name; } ;
struct head {int /*<<< orphan*/  number; struct id* last; struct id* first; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct id*) ; 
 scalar_t__ sequence_number ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 struct id* xcalloc (scalar_t__,int) ; 

__attribute__((used)) static void
add_to_list (struct head *head_ptr, const char *name)
{
  struct id *newid = xcalloc (sizeof (struct id) + strlen (name), 1);
  struct id *p;
  strcpy (newid->name, name);

  if (head_ptr->first)
    head_ptr->last->next = newid;
  else
    head_ptr->first = newid;

  /* Check for duplicate symbols.  */
  for (p = head_ptr->first;
       strcmp (name, p->name) != 0;
       p = p->next)
    ;
  if (p != newid)
    {
      head_ptr->last->next = 0;
      free (newid);
      return;
    }

  newid->sequence = ++sequence_number;
  head_ptr->last = newid;
  head_ptr->number++;
}