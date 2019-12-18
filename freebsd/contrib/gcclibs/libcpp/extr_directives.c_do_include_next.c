#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  enum include_type { ____Placeholder_include_type } include_type ;
struct TYPE_7__ {TYPE_1__* buffer; } ;
typedef  TYPE_2__ cpp_reader ;
struct TYPE_6__ {int /*<<< orphan*/  prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_DL_WARNING ; 
 int IT_INCLUDE ; 
 int IT_INCLUDE_NEXT ; 
 int /*<<< orphan*/  cpp_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  do_include_common (TYPE_2__*,int) ; 

__attribute__((used)) static void
do_include_next (cpp_reader *pfile)
{
  enum include_type type = IT_INCLUDE_NEXT;

  /* If this is the primary source file, warn and use the normal
     search logic.  */
  if (! pfile->buffer->prev)
    {
      cpp_error (pfile, CPP_DL_WARNING,
		 "#include_next in primary source file");
      type = IT_INCLUDE;
    }
  do_include_common (pfile, type);
}