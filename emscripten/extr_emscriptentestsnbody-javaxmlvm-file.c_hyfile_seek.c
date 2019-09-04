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
typedef  int off_t ;
typedef  int I_64 ;
typedef  int /*<<< orphan*/  I_32 ;
typedef  scalar_t__ IDATA ;

/* Variables and functions */
 int FD_BIAS ; 
 int /*<<< orphan*/  HySeekEnd ; 
 int /*<<< orphan*/  HySeekSet ; 
 int /*<<< orphan*/  lseek (int,int,int /*<<< orphan*/ ) ; 

I_64 hyfile_seek (IDATA inFD, I_64 offset, I_32 whence)
{
  int fd = (int)inFD;
  off_t localOffset = (off_t) offset;

  if ((whence < HySeekSet) || (whence > HySeekEnd))
    {
      return -1;
    }

  /* If file offsets are 32 bit, truncate the seek to that range */
  if (sizeof (off_t) < sizeof (I_64))
    {
      if (offset > 0x7FFFFFFF)
        {
          localOffset = 0x7FFFFFFF;
        }
      else if (offset < -0x7FFFFFFF)
        {
          localOffset = -0x7FFFFFFF;
        }
    }

#if (FD_BIAS != 0)
	if (fd < FD_BIAS) {
		/* Cannot seek on STD streams, and no other FD's should exist <FD_BIAS */
		return -1;
	}
#endif

  return (I_64) lseek ((int) (fd - FD_BIAS), localOffset, whence);
}