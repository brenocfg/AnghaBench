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
typedef  int /*<<< orphan*/  register_names ;

/* Variables and functions */

__attribute__((used)) static const char *
alpha_register_name (int regno)
{
  static const char * const register_names[] =
  {
    "v0",   "t0",   "t1",   "t2",   "t3",   "t4",   "t5",   "t6",
    "t7",   "s0",   "s1",   "s2",   "s3",   "s4",   "s5",   "fp",
    "a0",   "a1",   "a2",   "a3",   "a4",   "a5",   "t8",   "t9",
    "t10",  "t11",  "ra",   "t12",  "at",   "gp",   "sp",   "zero",
    "f0",   "f1",   "f2",   "f3",   "f4",   "f5",   "f6",   "f7",
    "f8",   "f9",   "f10",  "f11",  "f12",  "f13",  "f14",  "f15",
    "f16",  "f17",  "f18",  "f19",  "f20",  "f21",  "f22",  "f23",
    "f24",  "f25",  "f26",  "f27",  "f28",  "f29",  "f30",  "fpcr",
    "pc",   "",     "unique"
  };

  if (regno < 0)
    return NULL;
  if (regno >= (sizeof(register_names) / sizeof(*register_names)))
    return NULL;
  return register_names[regno];
}