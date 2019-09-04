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
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  dev_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_2__ {int (* d_ioctl ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  S_IFBLK ; 
 TYPE_1__* bdevsw ; 
 size_t major (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int file_ioctl(void * p1, void * p2, u_long theIoctl, caddr_t result)
{
    dev_t device = *(dev_t*) p1;

    return ((*bdevsw[major(device)].d_ioctl)
		    (device, theIoctl, result, S_IFBLK, p2));
}