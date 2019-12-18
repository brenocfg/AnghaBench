#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct comedi_device {int dummy; } ;
struct TYPE_3__ {int* dw_MolduleConfiguration; int b_BoardVersion; scalar_t__ ui_Address; } ;
struct TYPE_4__ {TYPE_1__ s_BoardInfos; } ;

/* Variables and functions */
 TYPE_2__* devpriv ; 
 void* inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 

int i_APCI1710_Reset(struct comedi_device *dev)
{
	int ret;
	unsigned int dw_Dummy;

	/*********************************/
	/* Read all module configuration */
	/*********************************/
	ret = inl(devpriv->s_BoardInfos.ui_Address + 60);
	devpriv->s_BoardInfos.dw_MolduleConfiguration[0] = ret;

	ret = inl(devpriv->s_BoardInfos.ui_Address + 124);
	devpriv->s_BoardInfos.dw_MolduleConfiguration[1] = ret;

	ret = inl(devpriv->s_BoardInfos.ui_Address + 188);
	devpriv->s_BoardInfos.dw_MolduleConfiguration[2] = ret;

	ret = inl(devpriv->s_BoardInfos.ui_Address + 252);
	devpriv->s_BoardInfos.dw_MolduleConfiguration[3] = ret;

	/*  outl(0x80808082,devpriv->s_BoardInfos.ui_Address+0x60); */
	outl(0x83838383, devpriv->s_BoardInfos.ui_Address + 0x60);

	devpriv->s_BoardInfos.b_BoardVersion = 1;

	/*  Enable the interrupt for the controler */
	dw_Dummy = inl(devpriv->s_BoardInfos.ui_Address + 0x38);
	outl(dw_Dummy | 0x2000, devpriv->s_BoardInfos.ui_Address + 0x38);

	return 0;
}