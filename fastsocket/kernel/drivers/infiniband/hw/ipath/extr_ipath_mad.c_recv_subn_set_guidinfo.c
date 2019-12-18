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
struct ib_smp {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int recv_subn_get_guidinfo (struct ib_smp*,struct ib_device*) ; 

__attribute__((used)) static int recv_subn_set_guidinfo(struct ib_smp *smp,
				  struct ib_device *ibdev)
{
	/* The only GUID we support is the first read-only entry. */
	return recv_subn_get_guidinfo(smp, ibdev);
}