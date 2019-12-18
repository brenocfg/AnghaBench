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
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  nv_error (void*,char*,int) ; 
 int nv_rdvgac (void*,int,int) ; 
 int nv_rdvgag (void*,int,int) ; 
 int nv_rdvgas (void*,int,int) ; 

u8
nv_rdvgai(void *obj, int head, u16 port, u8 index)
{
	if (port == 0x03c4) return nv_rdvgas(obj, head, index);
	if (port == 0x03ce) return nv_rdvgag(obj, head, index);
	if (port == 0x03d4) return nv_rdvgac(obj, head, index);
	nv_error(obj, "unknown indexed vga port 0x%04x\n", port);
	return 0x00;
}