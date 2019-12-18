#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  file_ptr ;
struct TYPE_16__ {char* name; } ;
typedef  TYPE_1__ const bfd_target ;
typedef  int bfd_size_type ;
typedef  scalar_t__ bfd_format ;
typedef  scalar_t__ bfd_error_type ;
typedef  int bfd_boolean ;
struct TYPE_17__ {scalar_t__ format; scalar_t__ direction; int output_has_begun; TYPE_1__ const* xvec; int /*<<< orphan*/  target_defaulted; } ;
typedef  TYPE_2__ bfd ;

/* Variables and functions */
 TYPE_1__ const* BFD_SEND_FMT (TYPE_2__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int FALSE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int TRUE ; 
 int /*<<< orphan*/  _bfd_check_format ; 
 int _bfd_target_vector_entries ; 
 scalar_t__ bfd_archive ; 
 TYPE_1__ const** bfd_associated_vector ; 
 TYPE_1__ const** bfd_default_vector ; 
 scalar_t__ bfd_error_file_ambiguously_recognized ; 
 scalar_t__ bfd_error_file_not_recognized ; 
 scalar_t__ bfd_error_invalid_operation ; 
 scalar_t__ bfd_error_wrong_format ; 
 scalar_t__ bfd_error_wrong_object_format ; 
 scalar_t__ bfd_get_error () ; 
 TYPE_1__ const** bfd_malloc (int) ; 
 int /*<<< orphan*/  bfd_read_p (TYPE_2__*) ; 
 scalar_t__ bfd_seek (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_error (scalar_t__) ; 
 TYPE_1__ const** bfd_target_vector ; 
 scalar_t__ bfd_type_end ; 
 scalar_t__ bfd_unknown ; 
 scalar_t__ both_direction ; 
 int /*<<< orphan*/  free (TYPE_1__ const**) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__ const**,TYPE_1__ const**,int) ; 

bfd_boolean
bfd_check_format_matches (bfd *abfd, bfd_format format, char ***matching)
{
  extern const bfd_target binary_vec;
  const bfd_target * const *target;
  const bfd_target **matching_vector = NULL;
  const bfd_target *save_targ, *right_targ, *ar_right_targ;
  int match_count;
  int ar_match_index;

  if (!bfd_read_p (abfd)
      || (unsigned int) abfd->format >= (unsigned int) bfd_type_end)
    {
      bfd_set_error (bfd_error_invalid_operation);
      return FALSE;
    }

  if (abfd->format != bfd_unknown)
    return abfd->format == format;

  /* Since the target type was defaulted, check them
     all in the hope that one will be uniquely recognized.  */
  save_targ = abfd->xvec;
  match_count = 0;
  ar_match_index = _bfd_target_vector_entries;

  if (matching)
    {
      bfd_size_type amt;

      *matching = NULL;
      amt = sizeof (*matching_vector) * 2 * _bfd_target_vector_entries;
      matching_vector = bfd_malloc (amt);
      if (!matching_vector)
	return FALSE;
    }

  right_targ = 0;
  ar_right_targ = 0;

  /* Presume the answer is yes.  */
  abfd->format = format;

  /* If the target type was explicitly specified, just check that target.  */
  if (!abfd->target_defaulted)
    {
      if (bfd_seek (abfd, (file_ptr) 0, SEEK_SET) != 0)	/* rewind! */
	{
	  if (matching)
	    free (matching_vector);
	  return FALSE;
	}

      right_targ = BFD_SEND_FMT (abfd, _bfd_check_format, (abfd));

      if (right_targ)
	{
	  abfd->xvec = right_targ;	/* Set the target as returned.  */

	  if (matching)
	    free (matching_vector);

	  /* If the file was opened for update, then `output_has_begun'
	     some time ago when the file was created.  Do not recompute
	     sections sizes or alignments in _bfd_set_section_contents.
	     We can not set this flag until after checking the format,
	     because it will interfere with creation of BFD sections.  */
	  if (abfd->direction == both_direction)
	    abfd->output_has_begun = TRUE;

	  return TRUE;			/* File position has moved, BTW.  */
	}

      /* For a long time the code has dropped through to check all
	 targets if the specified target was wrong.  I don't know why,
	 and I'm reluctant to change it.  However, in the case of an
	 archive, it can cause problems.  If the specified target does
	 not permit archives (e.g., the binary target), then we should
	 not allow some other target to recognize it as an archive, but
	 should instead allow the specified target to recognize it as an
	 object.  When I first made this change, it broke the PE target,
	 because the specified pei-i386 target did not recognize the
	 actual pe-i386 archive.  Since there may be other problems of
	 this sort, I changed this test to check only for the binary
	 target.  */
      if (format == bfd_archive && save_targ == &binary_vec)
	{
	  abfd->xvec = save_targ;
	  abfd->format = bfd_unknown;

	  if (matching)
	    free (matching_vector);

	  bfd_set_error (bfd_error_file_not_recognized);

	  return FALSE;
	}
    }

  for (target = bfd_target_vector; *target != NULL; target++)
    {
      const bfd_target *temp;
      bfd_error_type err;

      /* Don't check the default target twice.  */
      if (*target == &binary_vec
	  || (!abfd->target_defaulted && *target == save_targ))
	continue;

      abfd->xvec = *target;	/* Change BFD's target temporarily.  */

      if (bfd_seek (abfd, (file_ptr) 0, SEEK_SET) != 0)
	{
	  if (matching)
	    free (matching_vector);
	  return FALSE;
	}

      /* If _bfd_check_format neglects to set bfd_error, assume
	 bfd_error_wrong_format.  We didn't used to even pay any
	 attention to bfd_error, so I suspect that some
	 _bfd_check_format might have this problem.  */
      bfd_set_error (bfd_error_wrong_format);

      temp = BFD_SEND_FMT (abfd, _bfd_check_format, (abfd));

      if (temp)
	{
	  /* This format checks out as ok!  */
	  right_targ = temp;

	  /* If this is the default target, accept it, even if other
	     targets might match.  People who want those other targets
	     have to set the GNUTARGET variable.  */
	  if (temp == bfd_default_vector[0])
	    {
	      match_count = 1;
	      break;
	    }

	  if (matching)
	    matching_vector[match_count] = temp;

	  match_count++;
	}
      else if ((err = bfd_get_error ()) == bfd_error_wrong_object_format
	       || err == bfd_error_file_ambiguously_recognized)
	{
	  /* An archive with objects of the wrong type, or an
	     ambiguous match.  We want this target to match if we get
	     no better matches.  */
	  if (ar_right_targ != bfd_default_vector[0])
	    ar_right_targ = *target;
	  if (matching)
	    matching_vector[ar_match_index] = *target;
	  ar_match_index++;
	}
      else if (err != bfd_error_wrong_format)
	{
	  abfd->xvec = save_targ;
	  abfd->format = bfd_unknown;

	  if (matching)
	    free (matching_vector);

	  return FALSE;
	}
    }

  if (match_count == 0)
    {
      /* Try partial matches.  */
      right_targ = ar_right_targ;

      if (right_targ == bfd_default_vector[0])
	{
	  match_count = 1;
	}
      else
	{
	  match_count = ar_match_index - _bfd_target_vector_entries;

	  if (matching && match_count > 1)
	    memcpy (matching_vector,
		    matching_vector + _bfd_target_vector_entries,
		    sizeof (*matching_vector) * match_count);
	}
    }

  if (match_count > 1
      && bfd_associated_vector != NULL
      && matching)
    {
      const bfd_target * const *assoc = bfd_associated_vector;

      while ((right_targ = *assoc++) != NULL)
	{
	  int i = match_count;

	  while (--i >= 0)
	    if (matching_vector[i] == right_targ)
	      break;

	  if (i >= 0)
	    {
	      match_count = 1;
	      break;
	    }
	}
    }

  if (match_count == 1)
    {
      abfd->xvec = right_targ;		/* Change BFD's target permanently.  */

      if (matching)
	free (matching_vector);

      /* If the file was opened for update, then `output_has_begun'
	 some time ago when the file was created.  Do not recompute
	 sections sizes or alignments in _bfd_set_section_contents.
	 We can not set this flag until after checking the format,
	 because it will interfere with creation of BFD sections.  */
      if (abfd->direction == both_direction)
	abfd->output_has_begun = TRUE;

      return TRUE;			/* File position has moved, BTW.  */
    }

  abfd->xvec = save_targ;		/* Restore original target type.  */
  abfd->format = bfd_unknown;		/* Restore original format.  */

  if (match_count == 0)
    {
      bfd_set_error (bfd_error_file_not_recognized);

      if (matching)
	free (matching_vector);
    }
  else
    {
      bfd_set_error (bfd_error_file_ambiguously_recognized);

      if (matching)
	{
	  *matching = (char **) matching_vector;
	  matching_vector[match_count] = NULL;
	  /* Return target names.  This is a little nasty.  Maybe we
	     should do another bfd_malloc?  */
	  while (--match_count >= 0)
	    {
	      const char *name = matching_vector[match_count]->name;
	      *(const char **) &matching_vector[match_count] = name;
	    }
	}
    }

  return FALSE;
}