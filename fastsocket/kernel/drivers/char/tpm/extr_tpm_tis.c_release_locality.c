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
struct TYPE_2__ {scalar_t__ iobase; } ;
struct tpm_chip {TYPE_1__ vendor; } ;

/* Variables and functions */
 scalar_t__ TPM_ACCESS (int) ; 
 int /*<<< orphan*/  TPM_ACCESS_ACTIVE_LOCALITY ; 
 int TPM_ACCESS_REQUEST_PENDING ; 
 int TPM_ACCESS_VALID ; 
 int ioread8 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite8 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void release_locality(struct tpm_chip *chip, int l, int force)
{
	if (force || (ioread8(chip->vendor.iobase + TPM_ACCESS(l)) &
		      (TPM_ACCESS_REQUEST_PENDING | TPM_ACCESS_VALID)) ==
	    (TPM_ACCESS_REQUEST_PENDING | TPM_ACCESS_VALID))
		iowrite8(TPM_ACCESS_ACTIVE_LOCALITY,
			 chip->vendor.iobase + TPM_ACCESS(l));
}