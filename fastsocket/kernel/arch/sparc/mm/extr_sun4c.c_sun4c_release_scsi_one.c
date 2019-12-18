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
struct device {int dummy; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 scalar_t__ sun4c_iobuffer_start ; 
 int /*<<< orphan*/  sun4c_unlockarea (char*,unsigned long) ; 

__attribute__((used)) static void sun4c_release_scsi_one(struct device *dev, __u32 bufptr, unsigned long len)
{
	if (bufptr < sun4c_iobuffer_start)
		return; /* On kernel stack or similar, see above */
	sun4c_unlockarea((char *)bufptr, len);
}