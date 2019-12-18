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
 int /*<<< orphan*/  write_char (char) ; 
 int /*<<< orphan*/  write_unsigned_number (int const) ; 

__attribute__((used)) static void
write_discriminator (const int discriminator)
{
  /* If discriminator is zero, don't write anything.  Otherwise...  */
  if (discriminator > 0)
    {
      write_char ('_');
      write_unsigned_number (discriminator - 1);
    }
}