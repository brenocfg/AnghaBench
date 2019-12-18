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
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 scalar_t__ using_pc ; 
 scalar_t__ using_tcp ; 
 int write_large (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int write_small (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int
e7000_write_inferior_memory (CORE_ADDR memaddr, unsigned char *myaddr, int len)
{
  if (len < 16 || using_tcp || using_pc)
    return write_small (memaddr, myaddr, len);
  else
    return write_large (memaddr, myaddr, len);
}