#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* cmdSyntaxPtr ;
struct TYPE_3__ {unsigned char* cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ct54 ; 
 int /*<<< orphan*/  ct55 ; 

__attribute__((used)) static cmdSyntaxPtr
i2cmdBaudDef(int which, unsigned short rate)
{
	cmdSyntaxPtr pCM;

	switch(which)
	{
	case 1:
		pCM = (cmdSyntaxPtr) ct54;
		break;
	default:
	case 2:
		pCM = (cmdSyntaxPtr) ct55;
		break;
	}
	pCM->cmd[1] = (unsigned char) rate;
	pCM->cmd[2] = (unsigned char) (rate >> 8);
	return pCM;
}