#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int key; int flags; scalar_t__ id; struct TYPE_3__* next; } ;
typedef  TYPE_1__ rc_accelerator ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ACC_ALT ; 
 int ACC_CONTROL ; 
 int ACC_SHIFT ; 
 int ACC_VIRTKEY ; 
 scalar_t__ ISPRINT (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void
write_rc_accelerators (FILE *e, const rc_accelerator *accelerators)
{
  const rc_accelerator *acc;

  fprintf (e, "BEGIN\n");
  for (acc = accelerators; acc != NULL; acc = acc->next)
    {
      int printable;

      fprintf (e, "  ");

      if ((acc->key & 0x7f) == acc->key
	  && ISPRINT (acc->key)
	  && (acc->flags & ACC_VIRTKEY) == 0)
	{
	  fprintf (e, "\"%c\"", (char) acc->key);
	  printable = 1;
	}
      else
	{
	  fprintf (e, "%d", (int) acc->key);
	  printable = 0;
	}

      fprintf (e, ", %d", (int) acc->id);

      if (! printable)
	{
	  if ((acc->flags & ACC_VIRTKEY) != 0)
	    fprintf (e, ", VIRTKEY");
	  else
	    fprintf (e, ", ASCII");
	}

      if ((acc->flags & ACC_SHIFT) != 0)
	fprintf (e, ", SHIFT");
      if ((acc->flags & ACC_CONTROL) != 0)
	fprintf (e, ", CONTROL");
      if ((acc->flags & ACC_ALT) != 0)
	fprintf (e, ", ALT");

      fprintf (e, "\n");
    }

  fprintf (e, "END\n");
}