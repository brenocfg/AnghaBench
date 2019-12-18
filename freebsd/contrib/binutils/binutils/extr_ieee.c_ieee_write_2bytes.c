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
struct ieee_handle {int dummy; } ;
typedef  int bfd_boolean ;

/* Variables and functions */
 scalar_t__ ieee_write_byte (struct ieee_handle*,int) ; 

__attribute__((used)) static bfd_boolean
ieee_write_2bytes (struct ieee_handle *info, int i)
{
  return (ieee_write_byte (info, i >> 8)
	  && ieee_write_byte (info, i & 0xff));
}