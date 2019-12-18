#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char const* linkname; } ;
typedef  TYPE_1__ RASPISTILLYUV_STATE ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  create_filenames (char**,char**,char const*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ link (char const*,char*) ; 
 scalar_t__ rename (char const*,char const*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ symlink (char const*,char*) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 int /*<<< orphan*/  vcos_log_error (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rename_file(RASPISTILLYUV_STATE *state, FILE *output_file,
                        const char *final_filename, const char *use_filename, int frame)
{
   MMAL_STATUS_T status;

   fclose(output_file);
   vcos_assert(use_filename != NULL && final_filename != NULL);
   if (0 != rename(use_filename, final_filename))
   {
      vcos_log_error("Could not rename temp file to: %s; %s",
                     final_filename,strerror(errno));
   }
   if (state->linkname)
   {
      char *use_link;
      char *final_link;
      status = create_filenames(&final_link, &use_link, state->linkname, frame);

      // Create hard link if possible, symlink otherwise
      if (status != MMAL_SUCCESS
            || (0 != link(final_filename, use_link)
                &&  0 != symlink(final_filename, use_link))
            || 0 != rename(use_link, final_link))
      {
         vcos_log_error("Could not link as filename: %s; %s",
                        state->linkname,strerror(errno));
      }
      if (use_link) free(use_link);
      if (final_link) free(final_link);
   }
}