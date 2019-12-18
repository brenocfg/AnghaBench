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
typedef  int /*<<< orphan*/  time_t ;

/* Variables and functions */
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_WARN (char*,char*) ; 
 int /*<<< orphan*/  filestream_write_file (char*,void const*,size_t) ; 
 int /*<<< orphan*/  fill_pathname_application_data (char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  localtime (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,unsigned int,char*) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool dump_to_file_desperate(const void *data,
      size_t size, unsigned type)
{
   time_t time_;
   char *timebuf;
   char *path;
   char *application_data = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));
   application_data[0]    = '\0';

   if (!fill_pathname_application_data(application_data,
            PATH_MAX_LENGTH * sizeof(char)))
   {
      free(application_data);
      return false;
   }

   time(&time_);

   timebuf    = (char*)malloc(256 * sizeof(char));
   timebuf[0] = '\0';

   strftime(timebuf,
         256 * sizeof(char),
         "%Y-%m-%d-%H-%M-%S", localtime(&time_));

   path    = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));
   path[0] = '\0';
   snprintf(path,
         PATH_MAX_LENGTH * sizeof(char),
         "%s/RetroArch-recovery-%u%s",
         application_data, type,
         timebuf);

   free(application_data);
   free(timebuf);

   if (!filestream_write_file(path, data, size))
   {
      free(path);
      return false;
   }

   RARCH_WARN("Succeeded in saving RAM data to \"%s\".\n", path);
   free(path);
   return true;
}