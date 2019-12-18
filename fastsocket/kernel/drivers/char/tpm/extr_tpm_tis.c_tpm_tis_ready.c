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
struct TYPE_2__ {int /*<<< orphan*/  locality; scalar_t__ iobase; } ;
struct tpm_chip {TYPE_1__ vendor; } ;

/* Variables and functions */
 scalar_t__ TPM_STS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TPM_STS_COMMAND_READY ; 
 int /*<<< orphan*/  iowrite8 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void tpm_tis_ready(struct tpm_chip *chip)
{
	/* this causes the current command to be aborted */
	iowrite8(TPM_STS_COMMAND_READY,
		 chip->vendor.iobase + TPM_STS(chip->vendor.locality));
}