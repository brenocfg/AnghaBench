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
 int fromhex (char) ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 int sds_send (unsigned char*,int) ; 

__attribute__((used)) static void
sds_command (char *args, int from_tty)
{
  char *p;
  int i, len, retlen;
  unsigned char buf[1000];

  /* Convert hexadecimal chars into a byte buffer.  */
  p = args;
  len = 0;
  while (*p != '\0')
    {
      buf[len++] = fromhex (p[0]) * 16 + fromhex (p[1]);
      if (p[1] == '\0')
	break;
      p += 2;
    }

  retlen = sds_send (buf, len);

  printf_filtered ("Reply is ");
  for (i = 0; i < retlen; ++i)
    {
      printf_filtered ("%02x", buf[i]);
    }
  printf_filtered ("\n");
}