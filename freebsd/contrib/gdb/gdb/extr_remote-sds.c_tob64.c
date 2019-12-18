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
tob64 (unsigned char *inbuf, char *outbuf, int len)
{
  int i, sum;
  char *p;

  if (len % 3 != 0)
    error ("bad length");

  p = outbuf;
  for (i = 0; i < len; i += 3)
    {
      /* Collect the next three bytes into a number.  */
      sum = ((long) *inbuf++) << 16;
      sum |= ((long) *inbuf++) << 8;
      sum |= ((long) *inbuf++);

      /* Spit out 4 6-bit encodings.  */
      *p++ = ((sum >> 18) & 0x3f) + '0';
      *p++ = ((sum >> 12) & 0x3f) + '0';
      *p++ = ((sum >> 6) & 0x3f) + '0';
      *p++ = (sum & 0x3f) + '0';
    }
  return (p - outbuf);
}