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
typedef  enum rarch_dir_type { ____Placeholder_rarch_dir_type } rarch_dir_type ;
typedef  int /*<<< orphan*/  dir_system ;
typedef  int /*<<< orphan*/  dir_savestate ;
typedef  int /*<<< orphan*/  dir_savefile ;
typedef  int /*<<< orphan*/  current_savestate_dir ;
typedef  int /*<<< orphan*/  current_savefile_dir ;

/* Variables and functions */
#define  RARCH_DIR_CURRENT_SAVEFILE 133 
#define  RARCH_DIR_CURRENT_SAVESTATE 132 
#define  RARCH_DIR_NONE 131 
#define  RARCH_DIR_SAVEFILE 130 
#define  RARCH_DIR_SAVESTATE 129 
#define  RARCH_DIR_SYSTEM 128 

size_t dir_get_size(enum rarch_dir_type type)
{
   switch (type)
   {
      case RARCH_DIR_SYSTEM:
         return sizeof(dir_system);
      case RARCH_DIR_SAVESTATE:
         return sizeof(dir_savestate);
      case RARCH_DIR_CURRENT_SAVESTATE:
         return sizeof(current_savestate_dir);
      case RARCH_DIR_SAVEFILE:
         return sizeof(dir_savefile);
      case RARCH_DIR_CURRENT_SAVEFILE:
         return sizeof(current_savefile_dir);
      case RARCH_DIR_NONE:
         break;
   }

   return 0;
}