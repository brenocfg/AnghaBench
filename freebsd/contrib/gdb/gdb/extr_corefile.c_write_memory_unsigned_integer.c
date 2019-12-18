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
typedef  int /*<<< orphan*/  ULONGEST ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 char* alloca (int) ; 
 int /*<<< orphan*/  store_unsigned_integer (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_memory (int /*<<< orphan*/ ,char*,int) ; 

void
write_memory_unsigned_integer (CORE_ADDR addr, int len, ULONGEST value)
{
  char *buf = alloca (len);
  store_unsigned_integer (buf, len, value);
  write_memory (addr, buf, len);
}