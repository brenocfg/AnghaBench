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
typedef  int u32_t ;
typedef  int /*<<< orphan*/  u16_t ;

/* Variables and functions */
 int LWIP_CHKSUM (void*,int /*<<< orphan*/ ) ; 

u16_t
inet_chksum(void *dataptr, u16_t len)
{
  u32_t acc;

  acc = LWIP_CHKSUM(dataptr, len);
  while (acc >> 16) {
    acc = (acc & 0xffff) + (acc >> 16);
  }
  return (u16_t)~(acc & 0xffff);
}