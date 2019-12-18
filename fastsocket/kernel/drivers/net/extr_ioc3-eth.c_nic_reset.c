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
struct ioc3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ioc3_w_mcr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcr_pack (int,int) ; 
 int nic_wait (struct ioc3*) ; 

__attribute__((used)) static int nic_reset(struct ioc3 *ioc3)
{
        int presence;

	ioc3_w_mcr(mcr_pack(500, 65));
	presence = nic_wait(ioc3);

	ioc3_w_mcr(mcr_pack(0, 500));
	nic_wait(ioc3);

        return presence;
}