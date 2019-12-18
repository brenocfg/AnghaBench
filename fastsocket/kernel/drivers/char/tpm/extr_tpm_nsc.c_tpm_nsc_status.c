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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {scalar_t__ base; } ;
struct tpm_chip {TYPE_1__ vendor; } ;

/* Variables and functions */
 scalar_t__ NSC_STATUS ; 
 int /*<<< orphan*/  inb (scalar_t__) ; 

__attribute__((used)) static u8 tpm_nsc_status(struct tpm_chip *chip)
{
	return inb(chip->vendor.base + NSC_STATUS);
}