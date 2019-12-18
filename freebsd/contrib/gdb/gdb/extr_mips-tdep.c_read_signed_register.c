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
typedef  int /*<<< orphan*/  LONGEST ;

/* Variables and functions */
 void* alloca (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/  deprecated_read_register_gen (int,void*) ; 
 int /*<<< orphan*/  extract_signed_integer (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_size (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static LONGEST
read_signed_register (int regnum)
{
  void *buf = alloca (register_size (current_gdbarch, regnum));
  deprecated_read_register_gen (regnum, buf);
  return (extract_signed_integer
	  (buf, register_size (current_gdbarch, regnum)));
}