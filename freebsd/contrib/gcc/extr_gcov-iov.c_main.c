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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 unsigned long strtoul (char*,char**,int) ; 

int
main (int argc, char **argv)
{
  unsigned int version = 0;
  unsigned char v[4];
  unsigned int ix;
  unsigned long major;
  unsigned long minor = 0;
  char phase = 0;
  char *ptr;

  if (argc != 3)
    {
      fprintf (stderr, "usage: %s 'version' 'phase'\n", argv[0]);
      return 1;
    }

  ptr = argv[1];
  major = strtoul (ptr, &ptr, 10);

  if (*ptr == '.')
    minor = strtoul (ptr + 1, 0, 10);

  phase = argv[2][0];
  if (phase == '\0')
    phase = '*';

  v[0] = (major < 10 ? '0' : 'A' - 10) + major;
  v[1] = (minor / 10) + '0';
  v[2] = (minor % 10) + '0';
  v[3] = phase;

  for (ix = 0; ix != 4; ix++)
    version = (version << 8) | v[ix];

  printf ("/* Generated automatically by the program `%s'\n", argv[0]);
  printf ("   from `%s (%lu %lu) and %s (%c)'.  */\n",
	  argv[1], major, minor, argv[2], phase);
  printf ("\n");
  printf ("#define GCOV_VERSION ((gcov_unsigned_t)%#08x)  /* %.4s */\n",
	  version, v);

  return 0;
}