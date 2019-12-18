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
 int /*<<< orphan*/  RDP_MEM_WRITE ; 
 int /*<<< orphan*/  send_rdp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int,int*,int*) ; 

__attribute__((used)) static int
rdp_write (CORE_ADDR memaddr, char *buf, int len)
{
  int res;
  int val;

  send_rdp ("bww-p-SV", RDP_MEM_WRITE, memaddr, len, buf, len, &res, &val);

  if (res)
    {
      return val;
    }
  return len;
}