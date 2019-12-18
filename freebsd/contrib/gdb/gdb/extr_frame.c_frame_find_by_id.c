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
 scalar_t__ frame_id_eq (struct frame_id,struct frame_id) ; 
 scalar_t__ frame_id_inner (struct frame_id,struct frame_id) ; 
 int /*<<< orphan*/  frame_id_p (struct frame_id) ; 
 struct frame_info* get_current_frame () ; 
 struct frame_id get_frame_id (struct frame_info*) ; 
 struct frame_info* get_prev_frame (struct frame_info*) ; 

struct frame_info *
frame_find_by_id (struct frame_id id)
{
  struct frame_info *frame;

  /* ZERO denotes the null frame, let the caller decide what to do
     about it.  Should it instead return get_current_frame()?  */
  if (!frame_id_p (id))
    return NULL;

  for (frame = get_current_frame ();
       frame != NULL;
       frame = get_prev_frame (frame))
    {
      struct frame_id this = get_frame_id (frame);
      if (frame_id_eq (id, this))
	/* An exact match.  */
	return frame;
      if (frame_id_inner (id, this))
	/* Gone to far.  */
	return NULL;
      /* Either, we're not yet gone far enough out along the frame
         chain (inner(this,id), or we're comparing frameless functions
         (same .base, different .func, no test available).  Struggle
         on until we've definitly gone to far.  */
    }
  return NULL;
}