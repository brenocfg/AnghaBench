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
 scalar_t__ strchr (char const*,char) ; 

__attribute__((used)) static int
special_format (const char *fmt)
{
  return (strchr (fmt, '*') != 0
	  || strchr (fmt, 'V') != 0
	  || strchr (fmt, 'S') != 0
	  || strchr (fmt, 'n') != 0);
}