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
typedef  int u8 ;
struct ssb_bus {int dummy; } ;

/* Variables and functions */
 int COR_FUNC_ENA ; 
 int COR_IREQ_ENA ; 
 int COR_LEVEL_REQ ; 
 int COR_SOFT_RESET ; 
 int /*<<< orphan*/  msleep (int) ; 
 int ssb_pcmcia_cfg_read (struct ssb_bus*,int,int*) ; 
 int ssb_pcmcia_cfg_write (struct ssb_bus*,int,int) ; 

__attribute__((used)) static int ssb_pcmcia_cor_setup(struct ssb_bus *bus, u8 cor)
{
	u8 val;
	int err;

	err = ssb_pcmcia_cfg_read(bus, cor, &val);
	if (err)
		return err;
	val &= ~COR_SOFT_RESET;
	val |= COR_FUNC_ENA | COR_IREQ_ENA | COR_LEVEL_REQ;
	err = ssb_pcmcia_cfg_write(bus, cor, val);
	if (err)
		return err;
	msleep(40);

	return 0;
}