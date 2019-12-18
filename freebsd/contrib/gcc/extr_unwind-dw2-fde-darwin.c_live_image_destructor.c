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
struct live_images {int examined_p; int /*<<< orphan*/ * destructor; int /*<<< orphan*/ * fde; int /*<<< orphan*/ * object_info; } ;
struct km_object_info {int /*<<< orphan*/  unseen_objects; int /*<<< orphan*/  seen_objects; } ;

/* Variables and functions */
 int ALLOCED_IMAGE_MASK ; 
 int /*<<< orphan*/  KEYMGR_GCC3_DW2_OBJ_LIST ; 
 int /*<<< orphan*/  __deregister_frame_info_bases (int /*<<< orphan*/ *) ; 
 struct km_object_info* _keymgr_get_and_lock_processwide_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _keymgr_set_and_unlock_processwide_ptr (int /*<<< orphan*/ ,struct km_object_info*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seen_objects ; 
 int /*<<< orphan*/  unseen_objects ; 

__attribute__((used)) static void
live_image_destructor (struct live_images *image)
{
  if (image->object_info)
    {
      struct km_object_info *the_obj_info;

      the_obj_info =
	_keymgr_get_and_lock_processwide_ptr (KEYMGR_GCC3_DW2_OBJ_LIST);
      if (the_obj_info)
	{
	  seen_objects = the_obj_info->seen_objects;
	  unseen_objects = the_obj_info->unseen_objects;

	  /* Free any sorted arrays.  */
	  __deregister_frame_info_bases (image->fde);

	  the_obj_info->seen_objects = seen_objects;
	  the_obj_info->unseen_objects = unseen_objects;
	}
      _keymgr_set_and_unlock_processwide_ptr (KEYMGR_GCC3_DW2_OBJ_LIST,
					      the_obj_info);

      free (image->object_info);
      image->object_info = NULL;
      if (image->examined_p & ALLOCED_IMAGE_MASK)
	free (image->fde);
      image->fde = NULL;
    }
  image->examined_p = 0;
  image->destructor = NULL;
}