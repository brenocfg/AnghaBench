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
 int /*<<< orphan*/  MANGLE_TRACE (char*,char*) ; 
 int /*<<< orphan*/  write_char (char) ; 
 int /*<<< orphan*/  write_number (int const,int,int) ; 

__attribute__((used)) static void
write_substitution (const int seq_id)
{
  MANGLE_TRACE ("substitution", "");

  write_char ('S');
  if (seq_id > 0)
    write_number (seq_id - 1, /*unsigned=*/1, 36);
  write_char ('_');
}