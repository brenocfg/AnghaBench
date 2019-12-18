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
struct stat {scalar_t__ st_size; int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISFIFO (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISSOCK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_TYPEISMQ (struct stat const*) ; 
 scalar_t__ S_TYPEISSEM (struct stat const*) ; 
 scalar_t__ S_TYPEISSHM (struct stat const*) ; 
 scalar_t__ S_TYPEISTMO (struct stat const*) ; 
 char const* _ (char*) ; 

char const *
file_type (struct stat const *st)
{
  /* See POSIX 1003.1-2001 XCU Table 4-8 lines 17093-17107 for some of
     these formats.

     To keep diagnostics grammatical in English, the returned string
     must start with a consonant.  */

  if (S_ISREG (st->st_mode))
    return st->st_size == 0 ? _("regular empty file") : _("regular file");

  if (S_ISDIR (st->st_mode))
    return _("directory");

  if (S_ISBLK (st->st_mode))
    return _("block special file");

  if (S_ISCHR (st->st_mode))
    return _("character special file");

  if (S_ISFIFO (st->st_mode))
    return _("fifo");

  if (S_ISLNK (st->st_mode))
    return _("symbolic link");

  if (S_ISSOCK (st->st_mode))
    return _("socket");

  if (S_TYPEISMQ (st))
    return _("message queue");

  if (S_TYPEISSEM (st))
    return _("semaphore");

  if (S_TYPEISSHM (st))
    return _("shared memory object");

  if (S_TYPEISTMO (st))
    return _("typed memory object");

  return _("weird file");
}