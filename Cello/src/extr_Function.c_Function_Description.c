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

__attribute__((used)) static const char* Function_Description(void) {
  return
    "The `Function` type allows C function pointers to be treated as "
    "Cello objects. They can be passed around, stored, and manipulated. Only C "
    "functions of the type `var(*)(var)` can be stored as a `Function` type "
    "and when called the arguments will be wrapped into an iterable and passed "
    "as the first argument, typically in the form of a `tuple`.";
}