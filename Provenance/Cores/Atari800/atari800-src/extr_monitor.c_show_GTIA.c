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
 int GTIA_COLBK ; 
 int GTIA_COLPF0 ; 
 int GTIA_COLPF1 ; 
 int GTIA_COLPF2 ; 
 int GTIA_COLPF3 ; 
 int GTIA_COLPM0 ; 
 int GTIA_COLPM1 ; 
 int GTIA_COLPM2 ; 
 int GTIA_COLPM3 ; 
 int GTIA_GRACTL ; 
 int GTIA_GRAFM ; 
 int GTIA_GRAFP0 ; 
 int GTIA_GRAFP1 ; 
 int GTIA_GRAFP2 ; 
 int GTIA_GRAFP3 ; 
 int GTIA_HPOSM0 ; 
 int GTIA_HPOSM1 ; 
 int GTIA_HPOSM2 ; 
 int GTIA_HPOSM3 ; 
 int GTIA_HPOSP0 ; 
 int GTIA_HPOSP1 ; 
 int GTIA_HPOSP2 ; 
 int GTIA_HPOSP3 ; 
 int GTIA_PRIOR ; 
 int GTIA_SIZEM ; 
 int GTIA_SIZEP0 ; 
 int GTIA_SIZEP1 ; 
 int GTIA_SIZEP2 ; 
 int GTIA_SIZEP3 ; 
 int GTIA_VDELAY ; 
 int /*<<< orphan*/  printf (char*,int,int,int,...) ; 

__attribute__((used)) static void show_GTIA(void)
{
	printf("HPOSP0=%02X    HPOSP1=%02X    HPOSP2=%02X    HPOSP3=%02X\n",
		   GTIA_HPOSP0, GTIA_HPOSP1, GTIA_HPOSP2, GTIA_HPOSP3);
	printf("HPOSM0=%02X    HPOSM1=%02X    HPOSM2=%02X    HPOSM3=%02X\n",
		   GTIA_HPOSM0, GTIA_HPOSM1, GTIA_HPOSM2, GTIA_HPOSM3);
	printf("SIZEP0=%02X    SIZEP1=%02X    SIZEP2=%02X    SIZEP3=%02X    SIZEM= %02X\n",
		   GTIA_SIZEP0, GTIA_SIZEP1, GTIA_SIZEP2, GTIA_SIZEP3, GTIA_SIZEM);
	printf("GRAFP0=%02X    GRAFP1=%02X    GRAFP2=%02X    GRAFP3=%02X    GRAFM= %02X\n",
		   GTIA_GRAFP0, GTIA_GRAFP1, GTIA_GRAFP2, GTIA_GRAFP3, GTIA_GRAFM);
	printf("COLPM0=%02X    COLPM1=%02X    COLPM2=%02X    COLPM3=%02X\n",
		   GTIA_COLPM0, GTIA_COLPM1, GTIA_COLPM2, GTIA_COLPM3);
	printf("COLPF0=%02X    COLPF1=%02X    COLPF2=%02X    COLPF3=%02X    COLBK= %02X\n",
		   GTIA_COLPF0, GTIA_COLPF1, GTIA_COLPF2, GTIA_COLPF3, GTIA_COLBK);
	printf("PRIOR= %02X    VDELAY=%02X    GRACTL=%02X\n",
		   GTIA_PRIOR, GTIA_VDELAY, GTIA_GRACTL);
}