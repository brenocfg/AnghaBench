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
 scalar_t__ isspace (char) ; 

__attribute__((used)) static void
ep_skip_leading_whitespace (char **s)
{
  if ((s == NULL) || (*s == NULL))
    return;
  while (isspace (**s))
    *s += 1;
}