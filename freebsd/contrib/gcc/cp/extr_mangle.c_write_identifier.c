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
 int /*<<< orphan*/  MANGLE_TRACE (char*,char const*) ; 
 int /*<<< orphan*/  write_string (char const*) ; 

__attribute__((used)) static void
write_identifier (const char *identifier)
{
  MANGLE_TRACE ("identifier", identifier);
  write_string (identifier);
}