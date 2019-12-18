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
 int /*<<< orphan*/  RDP_CPU_READ ; 
 int /*<<< orphan*/  RDP_CPU_READWRITE_MODE_CURRENT ; 
 int /*<<< orphan*/  send_rdp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  store_signed_integer (char*,int,int) ; 

__attribute__((used)) static void
rdp_fetch_one_register (int mask, char *buf)
{
  int val;
  send_rdp ("bbw-SWZ", RDP_CPU_READ, RDP_CPU_READWRITE_MODE_CURRENT, mask, &val);
  store_signed_integer (buf, 4, val);
}