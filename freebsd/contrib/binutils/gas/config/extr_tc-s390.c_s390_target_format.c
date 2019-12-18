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
 int /*<<< orphan*/  init_default_arch () ; 
 int s390_arch_size ; 

const char *
s390_target_format ()
{
  /* We don't get a chance to initialize anything before we're called,
     so handle that now.  */
  init_default_arch ();

  return s390_arch_size == 64 ? "elf64-s390" : "elf32-s390";
}