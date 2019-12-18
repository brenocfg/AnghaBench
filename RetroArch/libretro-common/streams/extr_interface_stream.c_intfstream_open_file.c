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
typedef  int /*<<< orphan*/  intfstream_t ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ intfstream_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTFSTREAM_FILE ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intfstream_close (int /*<<< orphan*/ *) ; 
 scalar_t__ intfstream_init (TYPE_1__*) ; 
 int /*<<< orphan*/  intfstream_open (int /*<<< orphan*/ *,char const*,unsigned int,unsigned int) ; 

intfstream_t* intfstream_open_file(const char *path,
      unsigned mode, unsigned hints)
{
   intfstream_info_t info;
   intfstream_t *fd = NULL;

   info.type        = INTFSTREAM_FILE;
   fd               = (intfstream_t*)intfstream_init(&info);

   if (!fd)
      return NULL;

   if (!intfstream_open(fd, path, mode, hints))
      goto error;

   return fd;

error:
   if (fd)
   {
      intfstream_close(fd);
      free(fd);
   }
   return NULL;
}