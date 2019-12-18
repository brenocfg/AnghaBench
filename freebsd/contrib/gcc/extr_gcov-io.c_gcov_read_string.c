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
 unsigned int gcov_read_unsigned () ; 
 scalar_t__ gcov_read_words (unsigned int) ; 

const char *
gcov_read_string (void)
{
  unsigned length = gcov_read_unsigned ();
  
  if (!length)
    return 0;

  return (const char *) gcov_read_words (length);
}