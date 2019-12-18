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
struct inferior_status {int /*<<< orphan*/  registers; } ;
typedef  int /*<<< orphan*/  LONGEST ;

/* Variables and functions */
 int DEPRECATED_REGISTER_RAW_SIZE (int) ; 
 void* alloca (int) ; 
 int /*<<< orphan*/  regcache_raw_write (int /*<<< orphan*/ ,int,void*) ; 
 int /*<<< orphan*/  store_signed_integer (void*,int,int /*<<< orphan*/ ) ; 

void
write_inferior_status_register (struct inferior_status *inf_status, int regno,
				LONGEST val)
{
  int size = DEPRECATED_REGISTER_RAW_SIZE (regno);
  void *buf = alloca (size);
  store_signed_integer (buf, size, val);
  regcache_raw_write (inf_status->registers, regno, buf);
}