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
struct symtab_and_line {TYPE_2__* symtab; } ;
struct frame_info {int dummy; } ;
struct TYPE_4__ {TYPE_1__* objfile; int /*<<< orphan*/  filename; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ DEPRECATED_STREQ (int /*<<< orphan*/ ,char*) ; 
 struct frame_info* deprecated_selected_frame ; 
 int /*<<< orphan*/  find_frame_sal (struct frame_info*,struct symtab_and_line*) ; 
 struct frame_info* get_prev_frame (struct frame_info*) ; 
 int /*<<< orphan*/  is_ada_runtime_file (int /*<<< orphan*/ ) ; 

int
find_printable_frame (struct frame_info *fi, int level)
{
  struct symtab_and_line sal;

  for (; fi != NULL; level += 1, fi = get_prev_frame (fi))
    {
      find_frame_sal (fi, &sal);
      if (sal.symtab && !is_ada_runtime_file (sal.symtab->filename))
	{
#if defined(__alpha__) && defined(__osf__) && !defined(VXWORKS_TARGET)
	  /* libpthread.so contains some debugging information that prevents us
	     from finding the right frame */

	  if (sal.symtab->objfile &&
	      DEPRECATED_STREQ (sal.symtab->objfile->name, "/usr/shlib/libpthread.so"))
	    continue;
#endif
	  deprecated_selected_frame = fi;
	  break;
	}
    }

  return level;
}