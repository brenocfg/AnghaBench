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
typedef  int /*<<< orphan*/  gcov_unsigned_t ;

/* Variables and functions */
 int /*<<< orphan*/  from_file (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/ * gcov_read_words (int) ; 

gcov_unsigned_t
gcov_read_unsigned (void)
{
  gcov_unsigned_t value;
  const gcov_unsigned_t *buffer = gcov_read_words (1);

  if (!buffer)
    return 0;
  value = from_file (buffer[0]);
  return value;
}