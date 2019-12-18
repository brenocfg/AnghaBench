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
 scalar_t__ e7000_desc ; 
 int /*<<< orphan*/  serial_close (scalar_t__) ; 

__attribute__((used)) static void
e7000_close (int quitting)
{
  if (e7000_desc)
    {
      serial_close (e7000_desc);
      e7000_desc = 0;
    }
}