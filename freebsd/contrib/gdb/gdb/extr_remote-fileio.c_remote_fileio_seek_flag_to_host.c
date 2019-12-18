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
#define  FILEIO_SEEK_CUR 130 
#define  FILEIO_SEEK_END 129 
#define  FILEIO_SEEK_SET 128 
 int SEEK_CUR ; 
 int SEEK_END ; 
 int SEEK_SET ; 

__attribute__((used)) static int
remote_fileio_seek_flag_to_host (long num, int *flag)
{
  if (!flag)
    return 0;
  switch (num)
    {
      case FILEIO_SEEK_SET:
        *flag = SEEK_SET;
	break;
      case FILEIO_SEEK_CUR:
        *flag =  SEEK_CUR;
	break;
      case FILEIO_SEEK_END:
        *flag =  SEEK_END;
	break;
      default:
        return -1;
    }
  return 0;
}