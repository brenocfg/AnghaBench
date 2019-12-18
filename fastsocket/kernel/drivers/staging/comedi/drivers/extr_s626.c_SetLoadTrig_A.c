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
typedef  int uint16_t ;
struct enc_private {int /*<<< orphan*/  MyCRA; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int CRABIT_LOADSRC_A ; 
 scalar_t__ CRAMSK_LOADSRC_A ; 
 int /*<<< orphan*/  DEBIreplace (struct comedi_device*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void SetLoadTrig_A(struct comedi_device *dev, struct enc_private *k,
			  uint16_t Trig)
{
	DEBIreplace(dev, k->MyCRA, (uint16_t) (~CRAMSK_LOADSRC_A),
		    (uint16_t) (Trig << CRABIT_LOADSRC_A));
}