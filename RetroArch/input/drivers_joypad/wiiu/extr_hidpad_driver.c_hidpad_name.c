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
 char const* HID_PAD_NAME (unsigned int) ; 
 int /*<<< orphan*/  hidpad_query_pad (unsigned int) ; 

__attribute__((used)) static const char *hidpad_name(unsigned pad)
{
   if (!hidpad_query_pad(pad))
      return "N/A";

   return HID_PAD_NAME(pad);
}