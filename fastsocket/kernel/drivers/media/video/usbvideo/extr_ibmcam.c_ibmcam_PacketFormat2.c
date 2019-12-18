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
struct uvd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ibmcam_send_x_00_05 (struct uvd*,unsigned char) ; 
 int /*<<< orphan*/  ibmcam_send_x_00_05_02 (struct uvd*,unsigned char) ; 
 int /*<<< orphan*/  ibmcam_send_x_01_00_05 (struct uvd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unknown_88 ; 

__attribute__((used)) static void ibmcam_PacketFormat2(struct uvd *uvd, unsigned char fkey, unsigned char val)
{
	ibmcam_send_x_01_00_05	(uvd, unknown_88);
	ibmcam_send_x_00_05	(uvd, fkey);
	ibmcam_send_x_00_05_02	(uvd, val);
}