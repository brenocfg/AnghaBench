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
typedef  int CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,unsigned char*,int) ; 

__attribute__((used)) static int
mips_make_srec (char *buf, int type, CORE_ADDR memaddr, unsigned char *myaddr,
		int len)
{
  unsigned char checksum;
  int i;

  /* Create the header for the srec. addr_size is the number of bytes in the address,
     and 1 is the number of bytes in the count.  */

  /* FIXME!! bigger buf required for 64-bit! */
  buf[0] = 'S';
  buf[1] = type;
  buf[2] = len + 4 + 1;		/* len + 4 byte address + 1 byte checksum */
  /* This assumes S3 style downloads (4byte addresses). There should
     probably be a check, or the code changed to make it more
     explicit. */
  buf[3] = memaddr >> 24;
  buf[4] = memaddr >> 16;
  buf[5] = memaddr >> 8;
  buf[6] = memaddr;
  memcpy (&buf[7], myaddr, len);

  /* Note that the checksum is calculated on the raw data, not the
     hexified data.  It includes the length, address and the data
     portions of the packet.  */
  checksum = 0;
  buf += 2;			/* Point at length byte */
  for (i = 0; i < len + 4 + 1; i++)
    checksum += *buf++;

  *buf = ~checksum;

  return len + 8;
}