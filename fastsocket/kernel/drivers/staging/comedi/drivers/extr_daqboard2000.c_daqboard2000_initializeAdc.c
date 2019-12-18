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
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  daqboard2000_activateReferenceDacs (struct comedi_device*) ; 
 int /*<<< orphan*/  daqboard2000_adcDisarm (struct comedi_device*) ; 
 int /*<<< orphan*/  daqboard2000_initializeCtrs (struct comedi_device*) ; 
 int /*<<< orphan*/  daqboard2000_initializeTmrs (struct comedi_device*) ; 

__attribute__((used)) static void daqboard2000_initializeAdc(struct comedi_device *dev)
{
	daqboard2000_adcDisarm(dev);
	daqboard2000_activateReferenceDacs(dev);
	daqboard2000_initializeCtrs(dev);
	daqboard2000_initializeTmrs(dev);
}