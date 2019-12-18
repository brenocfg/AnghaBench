#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_target ;
struct TYPE_8__ {char const* filename; int /*<<< orphan*/  opened_once; int /*<<< orphan*/  direction; int /*<<< orphan*/ * iostream; } ;
typedef  TYPE_1__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _bfd_delete_bfd (TYPE_1__*) ; 
 TYPE_1__* _bfd_new_bfd () ; 
 int /*<<< orphan*/  bfd_cache_init (TYPE_1__*) ; 
 int /*<<< orphan*/  bfd_error_system_call ; 
 int /*<<< orphan*/ * bfd_find_target (char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  bfd_set_cacheable (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  both_direction ; 
 int /*<<< orphan*/ * fdopen (int,char const*) ; 
 int /*<<< orphan*/  read_direction ; 
 int /*<<< orphan*/ * real_fopen (char const*,char const*) ; 
 int /*<<< orphan*/  write_direction ; 

bfd *
bfd_fopen (const char *filename, const char *target, const char *mode, int fd)
{
  bfd *nbfd;
  const bfd_target *target_vec;

  nbfd = _bfd_new_bfd ();
  if (nbfd == NULL)
    return NULL;

  target_vec = bfd_find_target (target, nbfd);
  if (target_vec == NULL)
    {
      _bfd_delete_bfd (nbfd);
      return NULL;
    }
  
#ifdef HAVE_FDOPEN
  if (fd != -1)
    nbfd->iostream = fdopen (fd, mode);
  else
#endif
    nbfd->iostream = real_fopen (filename, mode);
  if (nbfd->iostream == NULL)
    {
      bfd_set_error (bfd_error_system_call);
      _bfd_delete_bfd (nbfd);
      return NULL;
    }

  /* OK, put everything where it belongs.  */
  nbfd->filename = filename;

  /* Figure out whether the user is opening the file for reading,
     writing, or both, by looking at the MODE argument.  */
  if ((mode[0] == 'r' || mode[0] == 'w' || mode[0] == 'a') 
      && mode[1] == '+')
    nbfd->direction = both_direction;
  else if (mode[0] == 'r')
    nbfd->direction = read_direction;
  else
    nbfd->direction = write_direction;

  if (! bfd_cache_init (nbfd))
    {
      _bfd_delete_bfd (nbfd);
      return NULL;
    }
  nbfd->opened_once = TRUE;
  /* If we opened the file by name, mark it cacheable; we can close it
     and reopen it later.  However, if a file descriptor was provided,
     then it may have been opened with special flags that make it
     unsafe to close and reopen the file.  */
  if (fd == -1)
    (void) bfd_set_cacheable (nbfd, TRUE);

  return nbfd;
}