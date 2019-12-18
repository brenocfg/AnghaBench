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
struct TYPE_3__ {int /*<<< orphan*/  line; int /*<<< orphan*/  file; } ;
struct conditional_frame {int dead_tree; int /*<<< orphan*/  macro_nest; TYPE_2__* previous_cframe; TYPE_1__ if_file_line; } ;
struct TYPE_4__ {scalar_t__ ignoring; } ;

/* Variables and functions */
 int /*<<< orphan*/  as_where (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* current_cframe ; 
 int /*<<< orphan*/  macro_nest ; 
 int /*<<< orphan*/  memset (struct conditional_frame*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
initialize_cframe (struct conditional_frame *cframe)
{
  memset (cframe, 0, sizeof (*cframe));
  as_where (&cframe->if_file_line.file,
	    &cframe->if_file_line.line);
  cframe->previous_cframe = current_cframe;
  cframe->dead_tree = current_cframe != NULL && current_cframe->ignoring;
  cframe->macro_nest = macro_nest;
}