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
union string_list_elem_attr {int /*<<< orphan*/  i; } ;

/* Variables and functions */
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RETRO_MEMORY_RTC ; 
 int /*<<< orphan*/  RETRO_MEMORY_SAVE_RAM ; 
 int /*<<< orphan*/  fill_pathname (char*,char const*,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  string_list_append (int /*<<< orphan*/ ,char const*,union string_list_elem_attr) ; 
 int /*<<< orphan*/  task_save_files ; 

void path_init_savefile_rtc(const char *savefile_path)
{
   union string_list_elem_attr attr;
   char *savefile_name_rtc = (char*)
      malloc(PATH_MAX_LENGTH * sizeof(char));

   savefile_name_rtc[0] = '\0';

   attr.i = RETRO_MEMORY_SAVE_RAM;
   string_list_append(task_save_files, savefile_path, attr);

   /* Infer .rtc save path from save ram path. */
   attr.i = RETRO_MEMORY_RTC;
   fill_pathname(savefile_name_rtc,
         savefile_path, ".rtc",
         PATH_MAX_LENGTH * sizeof(char));
   string_list_append(task_save_files, savefile_name_rtc, attr);
   free(savefile_name_rtc);
}