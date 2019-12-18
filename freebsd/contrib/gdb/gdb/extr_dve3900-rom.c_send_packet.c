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
typedef  int /*<<< orphan*/  hdr ;

/* Variables and functions */
 unsigned char PESC ; 
 int /*<<< orphan*/  debug_write (unsigned char*,int) ; 

__attribute__((used)) static void
send_packet (char type, unsigned char *buf, int buflen, int seq)
{
  unsigned char hdr[4];
  int len = buflen;
  int sum, i;

  /* If this is a 'p' packet, add one byte for a sequence number.  */
  if (type == 'p')
    len++;

  /* If the buffer has a non-zero length, add two bytes for a checksum.  */
  if (len > 0)
    len += 2;

  /* Write the packet header.  */
  hdr[0] = PESC;
  hdr[1] = type;
  hdr[2] = len & 0xff;
  hdr[3] = (len >> 8) & 0xff;
  debug_write (hdr, sizeof (hdr));

  if (len)
    {
      /* Write the packet data.  */
      debug_write (buf, buflen);

      /* Write the sequence number if this is a 'p' packet.  */
      if (type == 'p')
	{
	  hdr[0] = seq;
	  debug_write (hdr, 1);
	}

      /* Write the checksum.  */
      sum = 0;
      for (i = 0; i < buflen; i++)
	{
	  int tmp = (buf[i] & 0xff);
	  if (i & 1)
	    sum += tmp;
	  else
	    sum += tmp << 8;
	}
      if (type == 'p')
	{
	  if (buflen & 1)
	    sum += (seq & 0xff);
	  else
	    sum += (seq & 0xff) << 8;
	}
      sum = (sum & 0xffff) + ((sum >> 16) & 0xffff);
      sum += (sum >> 16) & 1;
      sum = ~sum;

      hdr[0] = (sum >> 8) & 0xff;
      hdr[1] = sum & 0xff;
      debug_write (hdr, 2);
    }
}