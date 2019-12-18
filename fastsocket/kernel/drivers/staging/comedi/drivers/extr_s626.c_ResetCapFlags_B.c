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
typedef  int /*<<< orphan*/  uint16_t ;
struct enc_private {int /*<<< orphan*/  MyCRB; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ CRBMSK_INTCTRL ; 
 int CRBMSK_INTRESETCMD ; 
 int CRBMSK_INTRESET_B ; 
 int /*<<< orphan*/  DEBIreplace (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ResetCapFlags_B(struct comedi_device *dev, struct enc_private *k)
{
	DEBIreplace(dev, k->MyCRB, (uint16_t) (~CRBMSK_INTCTRL),
		    CRBMSK_INTRESETCMD | CRBMSK_INTRESET_B);
}