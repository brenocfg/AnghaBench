#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int task_push_undo_save_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ undo_save_buf ; 

bool content_undo_save_state(void)
{
   return task_push_undo_save_state(undo_save_buf.path,
                             undo_save_buf.data,
                             undo_save_buf.size);
}