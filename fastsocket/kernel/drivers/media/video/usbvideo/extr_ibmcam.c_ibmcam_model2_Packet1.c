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
 int /*<<< orphan*/  ibmcam_model2_Packet2 (struct uvd*) ; 
 int /*<<< orphan*/  ibmcam_veio (struct uvd*,int /*<<< orphan*/ ,unsigned short,int) ; 

__attribute__((used)) static void ibmcam_model2_Packet1(struct uvd *uvd, unsigned short v1, unsigned short v2)
{
	ibmcam_veio(uvd, 0, 0x00aa, 0x012d);
	ibmcam_veio(uvd, 0, 0x00ff, 0x012e);
	ibmcam_veio(uvd, 0, v1,     0x012f);
	ibmcam_veio(uvd, 0, 0x00ff, 0x0130);
	ibmcam_veio(uvd, 0, 0xc719, 0x0124);
	ibmcam_veio(uvd, 0, v2,     0x0127);

	ibmcam_model2_Packet2(uvd);
}