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
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  bfd_size_type ;
typedef  int bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (char const*) ; 
 int FALSE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 unsigned long bfd_calc_gnu_debuglink_crc32 (unsigned long,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read (int,unsigned char*,int) ; 

__attribute__((used)) static bfd_boolean
separate_debug_file_exists (const char *name, const unsigned long crc)
{
  static unsigned char buffer [8 * 1024];
  unsigned long file_crc = 0;
  int fd;
  bfd_size_type count;

  BFD_ASSERT (name);

  fd = open (name, O_RDONLY);
  if (fd < 0)
    return FALSE;

  while ((count = read (fd, buffer, sizeof (buffer))) > 0)
    file_crc = bfd_calc_gnu_debuglink_crc32 (file_crc, buffer, count);

  close (fd);

  return crc == file_crc;
}