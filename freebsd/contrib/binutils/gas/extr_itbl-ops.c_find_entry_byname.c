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
struct itbl_entry {int /*<<< orphan*/  name; struct itbl_entry* next; } ;
typedef  int /*<<< orphan*/  e_type ;
typedef  int /*<<< orphan*/  e_processor ;

/* Variables and functions */
 struct itbl_entry** get_entries (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct itbl_entry *
find_entry_byname (e_processor processor,
		   e_type type, char *n)
{
  struct itbl_entry *e, **es;

  es = get_entries (processor, type);
  for (e = *es; e; e = e->next)	/* for each entry, ...  */
    {
      if (!strcmp (e->name, n))
	return e;
    }
  return 0;
}