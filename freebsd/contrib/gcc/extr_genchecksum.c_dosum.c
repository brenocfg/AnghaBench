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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ md5_stream (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  printf (char*,unsigned char,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 char* xstrerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dosum (const char *file)
{
  FILE *f;
  unsigned char result[16];
  int i;
  
  f = fopen (file, "rb");
  if (!f)
    {
      fprintf (stderr, "opening %s: %s\n", file, xstrerror (errno));
      exit (1);
    }
  
  /* Some executable formats have timestamps in the first 16 bytes, yuck.  */
  if (fseek (f, 16, SEEK_SET) != 0)
     {
      fprintf (stderr, "seeking in %s: %s\n", file, xstrerror (errno));
      exit (1);
    }
  
  if (md5_stream (f, result) != 0
      || fclose (f) != 0)
     {
      fprintf (stderr, "reading %s: %s\n", file, xstrerror (errno));
      exit (1);
    }

  fputs ("const unsigned char executable_checksum[16] = { ", stdout);
  for (i = 0; i < 16; i++)
    printf ("%#02x%s", result[i], i == 15 ? " };\n" : ", ");
}