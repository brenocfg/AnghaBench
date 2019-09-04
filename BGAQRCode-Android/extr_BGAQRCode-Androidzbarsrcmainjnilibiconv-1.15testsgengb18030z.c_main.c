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
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fclose (int /*<<< orphan*/ ) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int,int) ; 
 int /*<<< orphan*/  stdout ; 

int main ()
{
  int i1, i2, i3, i4, uc;

#if O_BINARY
  SET_BINARY(fileno(stdout));
#endif

  uc = 0x10000;
  for (i1 = 0x90; i1 <= 0xe3; i1++)
    for (i2 = 0x30; i2 <= 0x39; i2++)
      for (i3 = 0x81; i3 <= 0xfe; i3++)
        for (i4 = 0x30; i4 <= 0x39; i4++) {
          printf("0x%02X%02X%02X%02X\t0x%X\n", i1, i2, i3, i4, uc);
          uc++;
          if (uc == 0x110000)
            goto done;
        }
 done:

  if (ferror(stdout) || fclose(stdout))
    exit(1);
  exit(0);
}