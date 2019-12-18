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
 int /*<<< orphan*/  ibmcam_veio (struct uvd*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void ibmcam_model3_Packet1(struct uvd *uvd, unsigned short v1, unsigned short v2)
{
	ibmcam_veio(uvd, 0, 0x0078, 0x012d);
	ibmcam_veio(uvd, 0, v1,     0x012f);
	ibmcam_veio(uvd, 0, 0xd141, 0x0124);
	ibmcam_veio(uvd, 0, v2,     0x0127);
	ibmcam_veio(uvd, 0, 0xfea8, 0x0124);
}