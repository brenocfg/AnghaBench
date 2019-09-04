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
struct allocator {int /*<<< orphan*/  (* die ) (size_t) ;scalar_t__ (* allocate ) (size_t) ;int /*<<< orphan*/  (* free ) (char*) ;scalar_t__ (* reallocate ) (char*,size_t) ;} ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 int ENOMEM ; 
 int ERANGE ; 
 size_t SIZE_MAX ; 
 size_t SSIZE_MAX ; 
 int errno ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 struct allocator stdlib_allocator ; 
 int /*<<< orphan*/  stub1 (char*) ; 
 scalar_t__ stub2 (size_t) ; 
 scalar_t__ stub3 (char*,size_t) ; 
 int /*<<< orphan*/  stub4 (char*) ; 
 scalar_t__ stub5 (size_t) ; 
 int /*<<< orphan*/  stub6 (size_t) ; 

char *
careadlinkat (int fd, char const *filename,
              char *buffer, size_t buffer_size,
              struct allocator const *alloc,
              ssize_t (*preadlinkat) (int, char const *, char *, size_t))
{
  char *buf;
  size_t buf_size;
  size_t buf_size_max =
    SSIZE_MAX < SIZE_MAX ? (size_t) SSIZE_MAX + 1 : SIZE_MAX;
  char stack_buf[1024];

  if (! alloc)
    alloc = &stdlib_allocator;

  if (! buffer_size)
    {
      /* Allocate the initial buffer on the stack.  This way, in the
         common case of a symlink of small size, we get away with a
         single small malloc() instead of a big malloc() followed by a
         shrinking realloc().  */
      buffer = stack_buf;
      buffer_size = sizeof stack_buf;
    }

  buf = buffer;
  buf_size = buffer_size;

  do
    {
      /* Attempt to read the link into the current buffer.  */
      ssize_t link_length = preadlinkat (fd, filename, buf, buf_size);
      size_t link_size;
      if (link_length < 0)
        {
          /* On AIX 5L v5.3 and HP-UX 11i v2 04/09, readlink returns -1
             with errno == ERANGE if the buffer is too small.  */
          int readlinkat_errno = errno;
          if (readlinkat_errno != ERANGE)
            {
              if (buf != buffer)
                {
                  alloc->free (buf);
                  errno = readlinkat_errno;
                }
              return NULL;
            }
        }

      link_size = link_length;

      if (link_size < buf_size)
        {
          buf[link_size++] = '\0';

          if (buf == stack_buf)
            {
              char *b = (char *) alloc->allocate (link_size);
              buf_size = link_size;
              if (! b)
                break;
              memcpy (b, buf, link_size);
              buf = b;
            }
          else if (link_size < buf_size && buf != buffer && alloc->reallocate)
            {
              /* Shrink BUF before returning it.  */
              char *b = (char *) alloc->reallocate (buf, link_size);
              if (b)
                buf = b;
            }

          return buf;
        }

      if (buf != buffer)
        alloc->free (buf);

      if (buf_size <= buf_size_max / 2)
        buf_size *= 2;
      else if (buf_size < buf_size_max)
        buf_size = buf_size_max;
      else if (buf_size_max < SIZE_MAX)
        {
          errno = ENAMETOOLONG;
          return NULL;
        }
      else
        break;
      buf = (char *) alloc->allocate (buf_size);
    }
  while (buf);

  if (alloc->die)
    alloc->die (buf_size);
  errno = ENOMEM;
  return NULL;
}