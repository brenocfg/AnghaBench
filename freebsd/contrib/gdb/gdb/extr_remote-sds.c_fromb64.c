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
 int /*<<< orphan*/  error (char*) ; 

__attribute__((used)) static int
fromb64 (char *inbuf, char *outbuf, int len)
{
  int i, sum;

  if (len % 4 != 0)
    error ("bad length");

  for (i = 0; i < len; i += 4)
    {
      /* Collect 4 6-bit digits.  */
      sum = (*inbuf++ - '0') << 18;
      sum |= (*inbuf++ - '0') << 12;
      sum |= (*inbuf++ - '0') << 6;
      sum |= (*inbuf++ - '0');

      /* Now take the resulting 24-bit number and get three bytes out
         of it.  */
      *outbuf++ = (sum >> 16) & 0xff;
      *outbuf++ = (sum >> 8) & 0xff;
      *outbuf++ = sum & 0xff;
    }

  return (len / 4) * 3;
}