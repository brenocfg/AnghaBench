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
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int fileno (int /*<<< orphan*/ ) ; 
 scalar_t__ is_open (int) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
flush_stdout (void)
{
#if !_LIBC
  int stdout_fd;

# if GNULIB_FREOPEN_SAFER
  /* Use of gnulib's freopen-safer module normally ensures that
       fileno (stdout) == 1
     whenever stdout is open.  */
  stdout_fd = STDOUT_FILENO;
# else
  /* POSIX states that fileno (stdout) after fclose is unspecified.  But in
     practice it is not a problem, because stdout is statically allocated and
     the fd of a FILE stream is stored as a field in its allocated memory.  */
  stdout_fd = fileno (stdout);
# endif
  /* POSIX states that fflush (stdout) after fclose is unspecified; it
     is safe in glibc, but not on all other platforms.  fflush (NULL)
     is always defined, but too draconian.  */
  if (0 <= stdout_fd && is_open (stdout_fd))
#endif
    fflush (stdout);
}