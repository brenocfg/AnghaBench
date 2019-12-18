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
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  FOPEN_RB ; 
 int /*<<< orphan*/ * bfd_fopen (char const*,char const*,int /*<<< orphan*/ ,int) ; 

bfd *
bfd_openr (const char *filename, const char *target)
{
  return bfd_fopen (filename, target, FOPEN_RB, -1);
}