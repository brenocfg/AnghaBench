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
struct stat {int dummy; } ;

/* Variables and functions */
 scalar_t__ lstat (char*,struct stat*) ; 

__attribute__((used)) static int
f_exists(char *arg)
{
  struct stat buf;

  if (lstat(arg, &buf) < 0)
    return (0);
  else
    return (1);
}