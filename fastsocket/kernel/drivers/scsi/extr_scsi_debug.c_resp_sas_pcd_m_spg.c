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
typedef  int /*<<< orphan*/  sas_pcd_m_pg ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int resp_sas_pcd_m_spg(unsigned char * p, int pcontrol, int target,
			      int target_dev_id)
{	/* SAS phy control and discover mode page for mode_sense */
	unsigned char sas_pcd_m_pg[] = {0x59, 0x1, 0, 0x64, 0, 0x6, 0, 2,
		    0, 0, 0, 0, 0x10, 0x9, 0x8, 0x0,
		    0x52, 0x22, 0x22, 0x20, 0x0, 0x0, 0x0, 0x0,
		    0x51, 0x11, 0x11, 0x10, 0x0, 0x0, 0x0, 0x1,
		    0x2, 0, 0, 0, 0, 0, 0, 0,
		    0x88, 0x99, 0, 0, 0, 0, 0, 0,
		    0, 0, 0, 0, 0, 0, 0, 0,
		    0, 1, 0, 0, 0x10, 0x9, 0x8, 0x0,
		    0x52, 0x22, 0x22, 0x20, 0x0, 0x0, 0x0, 0x0,
		    0x51, 0x11, 0x11, 0x10, 0x0, 0x0, 0x0, 0x1,
		    0x3, 0, 0, 0, 0, 0, 0, 0,
		    0x88, 0x99, 0, 0, 0, 0, 0, 0,
		    0, 0, 0, 0, 0, 0, 0, 0,
		};
	int port_a, port_b;

	port_a = target_dev_id + 1;
	port_b = port_a + 1;
	memcpy(p, sas_pcd_m_pg, sizeof(sas_pcd_m_pg));
	p[20] = (port_a >> 24);
	p[21] = (port_a >> 16) & 0xff;
	p[22] = (port_a >> 8) & 0xff;
	p[23] = port_a & 0xff;
	p[48 + 20] = (port_b >> 24);
	p[48 + 21] = (port_b >> 16) & 0xff;
	p[48 + 22] = (port_b >> 8) & 0xff;
	p[48 + 23] = port_b & 0xff;
	if (1 == pcontrol)
		memset(p + 4, 0, sizeof(sas_pcd_m_pg) - 4);
	return sizeof(sas_pcd_m_pg);
}