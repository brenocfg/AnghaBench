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
typedef  int /*<<< orphan*/  len ;

/* Variables and functions */
 int MAXPSIZE ; 
 int /*<<< orphan*/  debug_write (unsigned char*,int) ; 
 int /*<<< orphan*/  ignore_packet () ; 
 int /*<<< orphan*/  send_packet (char,...) ; 
 int /*<<< orphan*/  write_long_le (unsigned char*,int) ; 

__attribute__((used)) static void
process_read_request (unsigned char *buf, int buflen)
{
  unsigned char len[4];
  int i, chunk;
  unsigned char seq;

  /* Discard the read request.  FIXME: we have to hope it's for
     the exact number of bytes we want to send; should check for this.  */
  ignore_packet ();

  for (i = chunk = 0, seq = 0; i < buflen; i += chunk, seq++)
    {
      /* Don't send more than MAXPSIZE bytes at a time.  */
      chunk = buflen - i;
      if (chunk > MAXPSIZE)
	chunk = MAXPSIZE;

      /* Write a packet containing the number of bytes we are sending.  */
      write_long_le (len, chunk);
      send_packet ('p', len, sizeof (len), seq);

      /* Write the data in raw form following the packet.  */
      debug_write (&buf[i], chunk);

      /* Discard the ACK packet.  */
      ignore_packet ();
    }

  /* Send an "end of data" packet.  */
  send_packet ('e', "", 0, 0);
}