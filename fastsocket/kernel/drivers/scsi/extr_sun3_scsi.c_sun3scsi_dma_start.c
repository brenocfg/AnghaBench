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
 int /*<<< orphan*/  UDC_CHN_START ; 
 int /*<<< orphan*/  UDC_CSR ; 
 int /*<<< orphan*/  sun3_udc_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int sun3scsi_dma_start(unsigned long count, unsigned char *data)
{

    sun3_udc_write(UDC_CHN_START, UDC_CSR);
    
    return 0;
}