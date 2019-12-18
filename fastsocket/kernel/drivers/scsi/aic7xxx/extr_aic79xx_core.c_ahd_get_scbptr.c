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
typedef  int u_int ;
struct ahd_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHD_ASSERT_MODES (struct ahd_softc*,int,int) ; 
 int AHD_MODE_CFG_MSK ; 
 int AHD_MODE_UNKNOWN_MSK ; 
 scalar_t__ SCBPTR ; 
 int ahd_inb (struct ahd_softc*,scalar_t__) ; 

u_int
ahd_get_scbptr(struct ahd_softc *ahd)
{
	AHD_ASSERT_MODES(ahd, ~(AHD_MODE_UNKNOWN_MSK|AHD_MODE_CFG_MSK),
			 ~(AHD_MODE_UNKNOWN_MSK|AHD_MODE_CFG_MSK));
	return (ahd_inb(ahd, SCBPTR) | (ahd_inb(ahd, SCBPTR + 1) << 8));
}