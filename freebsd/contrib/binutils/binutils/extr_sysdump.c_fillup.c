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
 int code ; 
 int /*<<< orphan*/  dh (unsigned char*,int) ; 
 scalar_t__ dump ; 
 int /*<<< orphan*/  file ; 
 int /*<<< orphan*/  fread (unsigned char*,int,int,int /*<<< orphan*/ ) ; 
 int getc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
fillup (unsigned char *ptr)
{
  int size;
  int sum;
  int i;

  size = getc (file) - 2;
  fread (ptr, 1, size, file);
  sum = code + size + 2;

  for (i = 0; i < size; i++)
    sum += ptr[i];

  if ((sum & 0xff) != 0xff)
    printf ("SUM IS %x\n", sum);

  if (dump)
    dh (ptr, size);

  return size - 1;
}