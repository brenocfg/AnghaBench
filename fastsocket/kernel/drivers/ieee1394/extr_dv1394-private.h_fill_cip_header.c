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
struct CIP_header {unsigned char* b; } ;
typedef  enum pal_or_ntsc { ____Placeholder_pal_or_ntsc } pal_or_ntsc ;

/* Variables and functions */
#define  DV1394_NTSC 129 
#define  DV1394_PAL 128 

__attribute__((used)) static inline void fill_cip_header(struct CIP_header *cip,
				   unsigned char source_node_id,
				   unsigned long counter,
				   enum pal_or_ntsc format,
				   unsigned long timestamp)
{
	cip->b[0] = source_node_id;
	cip->b[1] = 0x78; /* packet size in quadlets (480/4) - even for empty packets! */
	cip->b[2] = 0x00;
	cip->b[3] = counter;

	cip->b[4] = 0x80; /* const */

	switch(format) {
	case DV1394_PAL:
		cip->b[5] = 0x80;
		break;
	case DV1394_NTSC:
		cip->b[5] = 0x00;
		break;
	}

	cip->b[6] = timestamp >> 8;
	cip->b[7] = timestamp & 0xFF;
}