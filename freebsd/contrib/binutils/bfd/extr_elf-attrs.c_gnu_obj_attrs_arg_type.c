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
 int Tag_compatibility ; 

__attribute__((used)) static int
gnu_obj_attrs_arg_type (int tag)
{
  /* Except for Tag_compatibility, for GNU attributes we follow the
     same rule ARM ones > 32 follow: odd-numbered tags take strings
     and even-numbered tags take integers.  In addition, tag & 2 is
     nonzero for architecture-independent tags and zero for
     architecture-dependent ones.  */
  if (tag == Tag_compatibility)
    return 3;
  else
    return (tag & 1) != 0 ? 2 : 1;
}