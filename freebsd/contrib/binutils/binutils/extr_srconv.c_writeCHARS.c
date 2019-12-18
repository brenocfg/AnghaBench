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
 int /*<<< orphan*/  checksum (int /*<<< orphan*/ *,unsigned char*,int,int) ; 
 int code ; 
 int /*<<< orphan*/  memcpy (unsigned char*,char*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
writeCHARS (char *string, unsigned char *ptr, int *idx, int size, FILE *file)
{
  int i = *idx / 8;

  if (i > 240)
    {
      /* Lets write out that record and do another one.  */
      checksum (file, ptr, *idx, code | 0x1000);
      *idx = 16;
      i = *idx / 8;
    }

  if (size == 0)
    {
      /* Variable length string.  */
      size = strlen (string);
      ptr[i++] = size;
    }

  /* BUG WAITING TO HAPPEN.  */
  memcpy (ptr + i, string, size);
  i += size;
  *idx = i * 8;
}