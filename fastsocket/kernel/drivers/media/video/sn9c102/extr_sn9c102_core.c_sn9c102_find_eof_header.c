#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int member_0; int member_1; int member_2; int member_3; } ;
typedef  TYPE_3__ u8 ;
struct TYPE_6__ {scalar_t__ pixelformat; } ;
struct TYPE_7__ {TYPE_1__ pix_format; } ;
struct sn9c102_device {TYPE_2__ sensor; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_3__ const**) ; 
 scalar_t__ V4L2_PIX_FMT_JPEG ; 
 scalar_t__ V4L2_PIX_FMT_SN9C10X ; 
 int /*<<< orphan*/  memcmp (void*,TYPE_3__ const*,int) ; 

__attribute__((used)) static void*
sn9c102_find_eof_header(struct sn9c102_device* cam, void* mem, size_t len)
{
	static const u8 eof_header[4][4] = {
		{0x00, 0x00, 0x00, 0x00},
		{0x40, 0x00, 0x00, 0x00},
		{0x80, 0x00, 0x00, 0x00},
		{0xc0, 0x00, 0x00, 0x00},
	};
	size_t i, j;

	/* The EOF header does not exist in compressed data */
	if (cam->sensor.pix_format.pixelformat == V4L2_PIX_FMT_SN9C10X ||
	    cam->sensor.pix_format.pixelformat == V4L2_PIX_FMT_JPEG)
		return NULL;

	/*
	   The EOF header might cross the packet boundary, but this is not a
	   problem, since the end of a frame is determined by checking its size
	   in the first place.
	*/
	for (i = 0; (len >= 4) && (i <= len - 4); i++)
		for (j = 0; j < ARRAY_SIZE(eof_header); j++)
			if (!memcmp(mem + i, eof_header[j], 4))
				return mem + i;

	return NULL;
}