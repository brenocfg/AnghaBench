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

/* Variables and functions */
#define  RIO_AT 133 
 int /*<<< orphan*/  RIO_DEBUG_ROUTE ; 
#define  RIO_EISA 132 
#define  RIO_MCA 131 
#define  RIO_PCI 130 
#define  RIO_RTA 129 
#define  RIO_RTA_16 128 
 unsigned int TYPE_HOST ; 
 unsigned int TYPE_RTA16 ; 
 unsigned int TYPE_RTA8 ; 
 int /*<<< orphan*/  rio_dprintk (int /*<<< orphan*/ ,char*) ; 

unsigned int GetUnitType(unsigned int Uniq)
{
	switch ((Uniq >> 28) & 0xf) {
	case RIO_AT:
	case RIO_MCA:
	case RIO_EISA:
	case RIO_PCI:
		rio_dprintk(RIO_DEBUG_ROUTE, "Unit type: Host\n");
		return (TYPE_HOST);
	case RIO_RTA_16:
		rio_dprintk(RIO_DEBUG_ROUTE, "Unit type: 16 port RTA\n");
		return (TYPE_RTA16);
	case RIO_RTA:
		rio_dprintk(RIO_DEBUG_ROUTE, "Unit type: 8 port RTA\n");
		return (TYPE_RTA8);
	default:
		rio_dprintk(RIO_DEBUG_ROUTE, "Unit type: Unrecognised\n");
		return (99);
	}
}