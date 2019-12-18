#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int proto; } ;
struct TYPE_4__ {TYPE_1__ id; } ;
struct xfrm_userspi_info {int max; scalar_t__ min; TYPE_2__ info; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IPPROTO_AH 130 
#define  IPPROTO_COMP 129 
#define  IPPROTO_ESP 128 

__attribute__((used)) static int verify_userspi_info(struct xfrm_userspi_info *p)
{
	switch (p->info.id.proto) {
	case IPPROTO_AH:
	case IPPROTO_ESP:
		break;

	case IPPROTO_COMP:
		/* IPCOMP spi is 16-bits. */
		if (p->max >= 0x10000)
			return -EINVAL;
		break;

	default:
		return -EINVAL;
	}

	if (p->min > p->max)
		return -EINVAL;

	return 0;
}