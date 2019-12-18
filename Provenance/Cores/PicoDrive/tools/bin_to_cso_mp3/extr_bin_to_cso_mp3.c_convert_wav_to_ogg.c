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

/* Variables and functions */
 int MAX_PATH ; 
 int /*<<< orphan*/  chdir (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  system (char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

void convert_wav_to_ogg(char *wav_file_name, char *output_dir,
 char *ogg_file_name)
{
  char cmd_string[(MAX_PATH * 2) + 16];

  chdir(output_dir);
  sprintf(cmd_string, "oggenc %s", wav_file_name);
  system(cmd_string);

  unlink(wav_file_name);
  chdir("..");
}