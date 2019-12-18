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
typedef  unsigned int gcov_unsigned_t ;

/* Variables and functions */
 unsigned int* gcov_write_words (int) ; 
 int /*<<< orphan*/  memcpy (unsigned int*,char const*,unsigned int) ; 
 unsigned int strlen (char const*) ; 

void
gcov_write_string (const char *string)
{
  unsigned length = 0;
  unsigned alloc = 0;
  gcov_unsigned_t *buffer;

  if (string)
    {
      length = strlen (string);
      alloc = (length + 4) >> 2;
    }
  
  buffer = gcov_write_words (1 + alloc);

  buffer[0] = alloc;
  buffer[alloc] = 0;
  memcpy (&buffer[1], string, length);
}