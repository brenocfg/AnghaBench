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
 int /*<<< orphan*/ * gcov_write_words (int) ; 

void
gcov_write_unsigned (gcov_unsigned_t value)
{
  gcov_unsigned_t *buffer = gcov_write_words (1);

  buffer[0] = value;
}