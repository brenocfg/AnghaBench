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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_SINTEN ; 
 int /*<<< orphan*/  SIFACL ; 
 int /*<<< orphan*/  SIFWRITEB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tms380tr_enable_interrupts(struct net_device *dev)
{
	SIFWRITEB(ACL_SINTEN, SIFACL);

	return;
}