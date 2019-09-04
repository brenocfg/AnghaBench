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
#define  IFM_1000_CX 146 
#define  IFM_1000_LX 145 
#define  IFM_1000_SX 144 
#define  IFM_1000_TX 143 
#define  IFM_100_FX 142 
#define  IFM_100_T2 141 
#define  IFM_100_T4 140 
#define  IFM_100_TX 139 
#define  IFM_100_VG 138 
#define  IFM_10G_LR 137 
#define  IFM_10G_SR 136 
#define  IFM_10_2 135 
#define  IFM_10_5 134 
#define  IFM_10_FL 133 
#define  IFM_10_STP 132 
#define  IFM_10_T 131 
#define  IFM_2500_T 130 
#define  IFM_5000_T 129 
#define  IFM_HPNA_1 128 
 int IFM_SUBTYPE (int) ; 

__attribute__((used)) static int
link_speed(int active)
{
    switch (IFM_SUBTYPE(active)) {
    case IFM_10_T:
    case IFM_10_2:
    case IFM_10_5:
    case IFM_10_STP:
    case IFM_10_FL:
	return (10);
    case IFM_100_TX:
    case IFM_100_FX:
    case IFM_100_T4:
    case IFM_100_VG:
    case IFM_100_T2:
	return (100);
    case IFM_1000_SX:
    case IFM_1000_LX:
    case IFM_1000_CX:
    case IFM_1000_TX:
	return (1000);
    case IFM_HPNA_1:
	return (0);
    default:
	/* assume that new defined types are going to be at least 10GigE */
    case IFM_10G_SR:
    case IFM_10G_LR:
	return (10000);
    case IFM_2500_T:
	return (2500);
    case IFM_5000_T:
	return (5000);
    }
}