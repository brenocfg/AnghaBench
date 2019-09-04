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
 int /*<<< orphan*/  printf (char*,int,int,...) ; 
 int /*<<< orphan*/  stdout ; 

int main ()
{
  int i1, i2, i3;

#if O_BINARY
  SET_BINARY(fileno(stdout));
#endif

  /* Range 0x0000..0x007f */
  for (i1 = 0; i1 < 0x80; i1++)
    printf("0x%02X\t0x%04X\n", i1, i1);
  /* Range 0x0080..0x07ff */
  for (i1 = 2; i1 < 32; i1++)
    for (i2 = 0; i2 < 64; i2++)
      printf("0x%02X%02X\t0x%04X\n", 0xc0+i1,0x80+i2, (i1<<6)+i2);
  /* Range 0x0800..0xffff, except 0xd800..0xdfff */
  for (i1 = 0; i1 < 16; i1++)
    for (i2 = (i1==0 ? 32 : 0); i2 < 64; i2++)
      for (i3 = 0; i3 < 64; i3++) {
        int u = (i1<<12)+(i2<<6)+i3;
        if (!(u >= 0xd800 && u < 0xe000))
          printf("0x%02X%02X%02X\t0x%04X\n", 0xe0+i1,0x80+i2,0x80+i3, u);
      }

  if (ferror(stdout) || fclose(stdout))
    exit(1);
  exit(0);
}