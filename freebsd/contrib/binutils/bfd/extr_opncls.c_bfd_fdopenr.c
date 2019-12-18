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
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 char* FOPEN_RB ; 
 char* FOPEN_RUB ; 
 int /*<<< orphan*/  F_GETFL ; 
 int O_ACCMODE ; 
#define  O_RDONLY 130 
#define  O_RDWR 129 
#define  O_WRONLY 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  bfd_error_system_call ; 
 int /*<<< orphan*/ * bfd_fopen (char const*,char const*,char const*,int) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bfd *
bfd_fdopenr (const char *filename, const char *target, int fd)
{
  const char *mode;
#if defined(HAVE_FCNTL) && defined(F_GETFL)
  int fdflags;
#endif

#if ! defined(HAVE_FCNTL) || ! defined(F_GETFL)
  mode = FOPEN_RUB; /* Assume full access.  */
#else
  fdflags = fcntl (fd, F_GETFL, NULL);
  if (fdflags == -1)
    {
      bfd_set_error (bfd_error_system_call);
      return NULL;
    }

  /* (O_ACCMODE) parens are to avoid Ultrix header file bug.  */
  switch (fdflags & (O_ACCMODE))
    {
    case O_RDONLY: mode = FOPEN_RB; break;
    case O_WRONLY: mode = FOPEN_RUB; break;
    case O_RDWR:   mode = FOPEN_RUB; break;
    default: abort ();
    }
#endif

  return bfd_fopen (filename, target, mode, fd);
}