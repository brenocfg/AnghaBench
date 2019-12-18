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
struct frame_info {int dummy; } ;
struct frame_id {int dummy; } ;

/* Variables and functions */
 struct frame_info* frame_find_by_id (struct frame_id) ; 
 int /*<<< orphan*/  select_frame (struct frame_info*) ; 
 int /*<<< orphan*/  warning (char*) ; 

__attribute__((used)) static int
restore_selected_frame (void *args)
{
  struct frame_id *fid = (struct frame_id *) args;
  struct frame_info *frame;

  frame = frame_find_by_id (*fid);

  /* If inf_status->selected_frame_id is NULL, there was no previously
     selected frame.  */
  if (frame == NULL)
    {
      warning ("Unable to restore previously selected frame.\n");
      return 0;
    }

  select_frame (frame);

  return (1);
}