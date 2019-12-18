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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SONYPI_TYPE3_GID2 ; 
 int /*<<< orphan*/  pci_write_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ sonypi_device ; 
 int /*<<< orphan*/  sonypi_type2_dis () ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void sonypi_type3_dis(void)
{
	sonypi_type2_dis();
	udelay(10);
	pci_write_config_word(sonypi_device.dev, SONYPI_TYPE3_GID2, 0);
}