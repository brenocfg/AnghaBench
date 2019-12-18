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
 int /*<<< orphan*/  memcpy (char*,int,int) ; 
 int scrub_string ; 
 int scrub_string_end ; 

__attribute__((used)) static int
scrub_from_string (char *buf, int buflen)
{
  int copy;

  copy = scrub_string_end - scrub_string;
  if (copy > buflen)
    copy = buflen;
  memcpy (buf, scrub_string, copy);
  scrub_string += copy;
  return copy;
}