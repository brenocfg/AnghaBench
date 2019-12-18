#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
union ps3_firmware_version {scalar_t__ raw; void* rev; void* minor; void* major; scalar_t__ pad; } ;
typedef  void* u16 ;
struct TYPE_2__ {scalar_t__ raw; } ;

/* Variables and functions */
 TYPE_1__ ps3_firmware_version ; 

int ps3_compare_firmware_version(u16 major, u16 minor, u16 rev)
{
	union ps3_firmware_version x;

	x.pad = 0;
	x.major = major;
	x.minor = minor;
	x.rev = rev;

	return (ps3_firmware_version.raw > x.raw) -
	       (ps3_firmware_version.raw < x.raw);
}