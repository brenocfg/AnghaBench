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
struct TYPE_2__ {int /*<<< orphan*/  locality; scalar_t__ iobase; int /*<<< orphan*/  read_queue; int /*<<< orphan*/  timeout_c; } ;
struct tpm_chip {TYPE_1__ vendor; } ;

/* Variables and functions */
 scalar_t__ TPM_DATA_FIFO (int /*<<< orphan*/ ) ; 
 int TPM_STS_DATA_AVAIL ; 
 int TPM_STS_VALID ; 
 int get_burstcount (struct tpm_chip*) ; 
 int /*<<< orphan*/  ioread8 (scalar_t__) ; 
 scalar_t__ wait_for_tpm_stat (struct tpm_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int recv_data(struct tpm_chip *chip, u8 *buf, size_t count)
{
	int size = 0, burstcnt;
	while (size < count &&
	       wait_for_tpm_stat(chip,
				 TPM_STS_DATA_AVAIL | TPM_STS_VALID,
				 chip->vendor.timeout_c,
				 &chip->vendor.read_queue)
	       == 0) {
		burstcnt = get_burstcount(chip);
		for (; burstcnt > 0 && size < count; burstcnt--)
			buf[size++] = ioread8(chip->vendor.iobase +
					      TPM_DATA_FIFO(chip->vendor.
							    locality));
	}
	return size;
}