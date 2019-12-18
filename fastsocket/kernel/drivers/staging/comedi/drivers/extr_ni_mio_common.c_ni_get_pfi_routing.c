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
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int reg_type; } ;

/* Variables and functions */
 TYPE_1__ boardtype ; 
 int ni_m_series_get_pfi_routing (struct comedi_device*,unsigned int) ; 
 int ni_old_get_pfi_routing (struct comedi_device*,unsigned int) ; 
 int ni_reg_m_series_mask ; 

__attribute__((used)) static unsigned ni_get_pfi_routing(struct comedi_device *dev, unsigned chan)
{
	if (boardtype.reg_type & ni_reg_m_series_mask)
		return ni_m_series_get_pfi_routing(dev, chan);
	else
		return ni_old_get_pfi_routing(dev, chan);
}