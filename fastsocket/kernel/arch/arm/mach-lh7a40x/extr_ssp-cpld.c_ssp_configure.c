#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int device; int mode; int speed; int frame_size_write; int frame_size_read; } ;

/* Variables and functions */
 TYPE_1__ ssp_configuration ; 

__attribute__((used)) static int ssp_configure (int device, int mode, int speed,
			   int frame_size_write, int frame_size_read)
{
	ssp_configuration.device		= device;
	ssp_configuration.mode			= mode;
	ssp_configuration.speed			= speed;
	ssp_configuration.frame_size_write	= frame_size_write;
	ssp_configuration.frame_size_read	= frame_size_read;

	return 0;
}