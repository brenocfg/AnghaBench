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
typedef  scalar_t__ bfd_error_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  RETURN_NONFATAL (char const*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bfd_archive ; 
 scalar_t__ bfd_check_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_check_format_matches (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char***) ; 
 int /*<<< orphan*/  bfd_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_core ; 
 scalar_t__ bfd_error_file_ambiguously_recognized ; 
 scalar_t__ bfd_get_error () ; 
 char* bfd_get_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_nonfatal (char const*) ; 
 int /*<<< orphan*/  bfd_object ; 
 int /*<<< orphan*/ * bfd_openr (char const*,char const*) ; 
 int /*<<< orphan*/ * bfd_openw (char const*,char const*) ; 
 int /*<<< orphan*/  bfd_set_error (scalar_t__) ; 
 int /*<<< orphan*/  copy_archive (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_object (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char**) ; 
 int get_file_size (char const*) ; 
 int /*<<< orphan*/  list_matching_formats (char**) ; 
 int status ; 

__attribute__((used)) static void
copy_file (const char *input_filename, const char *output_filename,
	   const char *input_target,   const char *output_target)
{
  bfd *ibfd;
  char **obj_matching;
  char **core_matching;

  if (get_file_size (input_filename) < 1)
    {
      status = 1;
      return;
    }

  /* To allow us to do "strip *" without dying on the first
     non-object file, failures are nonfatal.  */
  ibfd = bfd_openr (input_filename, input_target);
  if (ibfd == NULL)
    RETURN_NONFATAL (input_filename);

  if (bfd_check_format (ibfd, bfd_archive))
    {
      bfd_boolean force_output_target;
      bfd *obfd;

      /* bfd_get_target does not return the correct value until
         bfd_check_format succeeds.  */
      if (output_target == NULL)
	{
	  output_target = bfd_get_target (ibfd);
	  force_output_target = FALSE;
	}
      else
	force_output_target = TRUE;

      obfd = bfd_openw (output_filename, output_target);
      if (obfd == NULL)
	RETURN_NONFATAL (output_filename);

      copy_archive (ibfd, obfd, output_target, force_output_target);
    }
  else if (bfd_check_format_matches (ibfd, bfd_object, &obj_matching))
    {
      bfd *obfd;
    do_copy:

      /* bfd_get_target does not return the correct value until
         bfd_check_format succeeds.  */
      if (output_target == NULL)
	output_target = bfd_get_target (ibfd);

      obfd = bfd_openw (output_filename, output_target);
      if (obfd == NULL)
	RETURN_NONFATAL (output_filename);

      if (! copy_object (ibfd, obfd))
	status = 1;

      if (!bfd_close (obfd))
	RETURN_NONFATAL (output_filename);

      if (!bfd_close (ibfd))
	RETURN_NONFATAL (input_filename);

    }
  else
    {
      bfd_error_type obj_error = bfd_get_error ();
      bfd_error_type core_error;

      if (bfd_check_format_matches (ibfd, bfd_core, &core_matching))
	{
	  /* This probably can't happen..  */
	  if (obj_error == bfd_error_file_ambiguously_recognized)
	    free (obj_matching);
	  goto do_copy;
	}

      core_error = bfd_get_error ();
      /* Report the object error in preference to the core error.  */
      if (obj_error != core_error)
	bfd_set_error (obj_error);

      bfd_nonfatal (input_filename);

      if (obj_error == bfd_error_file_ambiguously_recognized)
	{
	  list_matching_formats (obj_matching);
	  free (obj_matching);
	}
      if (core_error == bfd_error_file_ambiguously_recognized)
	{
	  list_matching_formats (core_matching);
	  free (core_matching);
	}

      status = 1;
    }
}