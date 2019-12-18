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
struct itbl_entry {char* name; unsigned long value; struct itbl_entry* next; int /*<<< orphan*/  type; int /*<<< orphan*/  processor; } ;
typedef  int /*<<< orphan*/  e_type ;
typedef  int /*<<< orphan*/  e_processor ;

/* Variables and functions */
 struct itbl_entry** get_entries (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (struct itbl_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static struct itbl_entry *
alloc_entry (e_processor processor, e_type type,
	     char *name, unsigned long value)
{
  struct itbl_entry *e, **es;
  if (!name)
    return 0;
  e = (struct itbl_entry *) malloc (sizeof (struct itbl_entry));
  if (e)
    {
      memset (e, 0, sizeof (struct itbl_entry));
      e->name = (char *) malloc (sizeof (strlen (name)) + 1);
      if (e->name)
	strcpy (e->name, name);
      e->processor = processor;
      e->type = type;
      e->value = value;
      es = get_entries (e->processor, e->type);
      e->next = *es;
      *es = e;
    }
  return e;
}