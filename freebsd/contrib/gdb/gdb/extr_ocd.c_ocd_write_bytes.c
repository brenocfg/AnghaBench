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
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  OCD_WRITE_MEM ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  ocd_error (char*,int) ; 
 unsigned char* ocd_get_packet (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocd_put_packet (char*,int) ; 
 int /*<<< orphan*/  remote_timeout ; 
 char write_mem_command ; 

int
ocd_write_bytes (CORE_ADDR memaddr, char *myaddr, int len)
{
  char buf[256 + 10];
  unsigned char *p;
  int origlen;

  origlen = len;

  buf[0] = write_mem_command;
  buf[5] = 1;			/* Write as bytes */
  buf[6] = 0;			/* Don't verify */

  while (len > 0)
    {
      int numbytes;
      int pktlen;
      int status, error_code;

      numbytes = min (len, 256 - 8);

      buf[1] = memaddr >> 24;
      buf[2] = memaddr >> 16;
      buf[3] = memaddr >> 8;
      buf[4] = memaddr;

      buf[7] = numbytes;

      memcpy (&buf[8], myaddr, numbytes);
      ocd_put_packet (buf, 8 + numbytes);
      p = ocd_get_packet (OCD_WRITE_MEM, &pktlen, remote_timeout);
      if (pktlen < 3)
	error ("Truncated response packet from OCD device");

      status = p[1];
      error_code = p[2];

      if (error_code == 0x11)	/* Got a bus error? */
	{
	  CORE_ADDR error_address;

	  error_address = p[3] << 24;
	  error_address |= p[4] << 16;
	  error_address |= p[5] << 8;
	  error_address |= p[6];
	  numbytes = error_address - memaddr;

	  len -= numbytes;

	  errno = EIO;

	  break;
	}
      else if (error_code != 0)
	ocd_error ("ocd_write_bytes:", error_code);

      len -= numbytes;
      memaddr += numbytes;
      myaddr += numbytes;
    }

  return origlen - len;
}