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
typedef  int u16 ;

/* Variables and functions */
#define  CODEC_TYPE_ZR36016 130 
#define  CODEC_TYPE_ZR36050 129 
#define  CODEC_TYPE_ZR36060 128 

__attribute__((used)) static char *
codecid_to_modulename (u16 codecid)
{
	char *name = NULL;

	switch (codecid) {
	case CODEC_TYPE_ZR36060:
		name = "zr36060";
		break;
	case CODEC_TYPE_ZR36050:
		name = "zr36050";
		break;
	case CODEC_TYPE_ZR36016:
		name = "zr36016";
		break;
	}

	return name;
}