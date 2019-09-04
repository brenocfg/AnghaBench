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
typedef  size_t dev_t ;
struct TYPE_2__ {int /*<<< orphan*/  d_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_DISK ; 
 size_t NODEV ; 
#define  VBLK 129 
#define  VCHR 128 
 TYPE_1__* bdevsw ; 
 size_t chrtoblk (size_t) ; 
 size_t major (size_t) ; 

int
isdisk(dev_t dev, int type)
{
	dev_t	maj = major(dev);

	switch (type) {
	case VCHR:
		maj = chrtoblk(maj);
		if (maj == NODEV) {
			break;
		}
		/* FALL THROUGH */
	case VBLK:
		if (bdevsw[maj].d_type == D_DISK) {
			return (1);
		}
		break;
	}
	return(0);
}