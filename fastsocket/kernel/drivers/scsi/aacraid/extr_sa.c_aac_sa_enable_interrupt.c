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
struct aac_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  PRICLEARIRQMASK; } ;

/* Variables and functions */
 int DOORBELL_1 ; 
 int DOORBELL_2 ; 
 int DOORBELL_3 ; 
 int DOORBELL_4 ; 
 int PrintfReady ; 
 TYPE_1__ SaDbCSR ; 
 int /*<<< orphan*/  sa_writew (struct aac_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void aac_sa_enable_interrupt (struct aac_dev *dev)
{
	sa_writew(dev, SaDbCSR.PRICLEARIRQMASK, (PrintfReady | DOORBELL_1 |
				DOORBELL_2 | DOORBELL_3 | DOORBELL_4));
}