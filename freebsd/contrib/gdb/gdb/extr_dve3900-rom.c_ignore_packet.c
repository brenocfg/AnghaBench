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
 int PESC ; 
 int debug_readchar (int) ; 
 int /*<<< orphan*/  error (char*,int) ; 

__attribute__((used)) static void
ignore_packet (void)
{
  int c = -1;
  int len;

  /* Ignore lots of trash (messages about section addresses, for example)
     until we see the start of a packet.  */
  for (len = 0; len < 256; len++)
    {
      c = debug_readchar (0);
      if (c == PESC)
	break;
    }
  if (len == 8)
    error ("Packet header byte not found; %02x seen instead.", c);

  /* Read the packet type and length.  */
  c = debug_readchar (1);	/* type */

  c = debug_readchar (1);	/* low byte of length */
  len = c & 0xff;

  c = debug_readchar (1);	/* high byte of length */
  len += (c & 0xff) << 8;

  /* Ignore the rest of the packet.  */
  while (len-- > 0)
    c = debug_readchar (1);
}