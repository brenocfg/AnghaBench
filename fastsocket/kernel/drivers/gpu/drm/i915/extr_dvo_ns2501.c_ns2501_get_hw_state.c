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
struct intel_dvo_device {int dummy; } ;

/* Variables and functions */
 unsigned char NS2501_8_PD ; 
 int /*<<< orphan*/  NS2501_REG8 ; 
 int /*<<< orphan*/  ns2501_readb (struct intel_dvo_device*,int /*<<< orphan*/ ,unsigned char*) ; 

__attribute__((used)) static bool ns2501_get_hw_state(struct intel_dvo_device *dvo)
{
	unsigned char ch;

	if (!ns2501_readb(dvo, NS2501_REG8, &ch))
		return false;

	if (ch & NS2501_8_PD)
		return true;
	else
		return false;
}