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
typedef  int /*<<< orphan*/  config_file_t ;

/* Variables and functions */
 int /*<<< orphan*/ * config_file_new_from_path_to_string (char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* video_shader_read_reference_path (char const*) ; 

config_file_t *video_shader_read_preset(const char *path)
{
   config_file_t *conf;
   char *reference = video_shader_read_reference_path(path);
   if (reference)
   {
      conf = config_file_new_from_path_to_string(reference);
      free(reference);
   }
   else
      conf = config_file_new_from_path_to_string(path);

   return conf;
}