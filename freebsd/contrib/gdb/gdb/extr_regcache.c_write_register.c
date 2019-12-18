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
typedef  scalar_t__ LONGEST ;

/* Variables and functions */
 int DEPRECATED_REGISTER_RAW_SIZE (int) ; 
 void* alloca (int) ; 
 int /*<<< orphan*/  deprecated_write_register_gen (int,void*) ; 
 int /*<<< orphan*/  store_signed_integer (void*,int,scalar_t__) ; 

void
write_register (int regnum, LONGEST val)
{
  void *buf;
  int size;
  size = DEPRECATED_REGISTER_RAW_SIZE (regnum);
  buf = alloca (size);
  store_signed_integer (buf, size, (LONGEST) val);
  deprecated_write_register_gen (regnum, buf);
}