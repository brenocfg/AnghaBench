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

/* Variables and functions */
 int /*<<< orphan*/  H1940_SUSPEND_CHECK ; 
 int /*<<< orphan*/  H1940_SUSPEND_CHECKSUM ; 
 int /*<<< orphan*/  S3C2410_GPF (int) ; 
 void* S3C2410_GSTATUS3 ; 
 void* S3C2410_GSTATUS4 ; 
 int /*<<< orphan*/  S3C_PMDBG (char*,scalar_t__) ; 
 scalar_t__ __raw_readl (void*) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,void*) ; 
 scalar_t__ machine_is_aml_m5900 () ; 
 scalar_t__ machine_is_h1940 () ; 
 scalar_t__ machine_is_rx3715 () ; 
 void* phys_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c2410_gpio_setpin (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s3c_cpu_resume ; 
 unsigned long virt_to_phys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s3c2410_pm_prepare(void)
{
	/* ensure at least GSTATUS3 has the resume address */

	__raw_writel(virt_to_phys(s3c_cpu_resume), S3C2410_GSTATUS3);

	S3C_PMDBG("GSTATUS3 0x%08x\n", __raw_readl(S3C2410_GSTATUS3));
	S3C_PMDBG("GSTATUS4 0x%08x\n", __raw_readl(S3C2410_GSTATUS4));

	if (machine_is_h1940()) {
		void *base = phys_to_virt(H1940_SUSPEND_CHECK);
		unsigned long ptr;
		unsigned long calc = 0;

		/* generate check for the bootloader to check on resume */

		for (ptr = 0; ptr < 0x40000; ptr += 0x400)
			calc += __raw_readl(base+ptr);

		__raw_writel(calc, phys_to_virt(H1940_SUSPEND_CHECKSUM));
	}

	/* the RX3715 uses similar code and the same H1940 and the
	 * same offsets for resume and checksum pointers */

	if (machine_is_rx3715()) {
		void *base = phys_to_virt(H1940_SUSPEND_CHECK);
		unsigned long ptr;
		unsigned long calc = 0;

		/* generate check for the bootloader to check on resume */

		for (ptr = 0; ptr < 0x40000; ptr += 0x4)
			calc += __raw_readl(base+ptr);

		__raw_writel(calc, phys_to_virt(H1940_SUSPEND_CHECKSUM));
	}

	if ( machine_is_aml_m5900() )
		s3c2410_gpio_setpin(S3C2410_GPF(2), 1);

}