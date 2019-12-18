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
typedef  scalar_t__ u32 ;
struct capincci {scalar_t__ ncci; struct capincci* next; } ;
struct capidev {struct capincci* nccis; } ;

/* Variables and functions */

__attribute__((used)) static struct capincci *capincci_find(struct capidev *cdev, u32 ncci)
{
	struct capincci *p;

	for (p=cdev->nccis; p ; p = p->next) {
		if (p->ncci == ncci)
			break;
	}
	return p;
}