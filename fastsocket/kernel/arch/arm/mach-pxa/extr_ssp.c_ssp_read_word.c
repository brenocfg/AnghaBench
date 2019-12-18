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
typedef  int u32 ;
struct ssp_device {scalar_t__ mmio_base; } ;
struct ssp_dev {struct ssp_device* ssp; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ SSDR ; 
 scalar_t__ SSSR ; 
 int SSSR_RNE ; 
 int TIMEOUT ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  cpu_relax () ; 

int ssp_read_word(struct ssp_dev *dev, u32 *data)
{
	struct ssp_device *ssp = dev->ssp;
	int timeout = TIMEOUT;

	while (!(__raw_readl(ssp->mmio_base + SSSR) & SSSR_RNE)) {
	        if (!--timeout)
	        	return -ETIMEDOUT;
		cpu_relax();
	}

	*data = __raw_readl(ssp->mmio_base + SSDR);
	return 0;
}