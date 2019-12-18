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
struct charset {int /*<<< orphan*/  name; int /*<<< orphan*/  valid_host_charset; } ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_valid_host_charset (struct charset *cs)
{
  if (! cs->valid_host_charset)
    error ("GDB can't use `%s' as its host character set.", cs->name);
}