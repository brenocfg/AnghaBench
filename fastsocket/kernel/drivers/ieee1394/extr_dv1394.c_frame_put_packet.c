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
struct packet {int* data; } ;
struct frame {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,int*,int) ; 

__attribute__((used)) static void inline
frame_put_packet (struct frame *f, struct packet *p)
{
	int section_type = p->data[0] >> 5;           /* section type is in bits 5 - 7 */
	int dif_sequence = p->data[1] >> 4;           /* dif sequence number is in bits 4 - 7 */
	int dif_block = p->data[2];

	/* sanity check */
	if (dif_sequence > 11 || dif_block > 149) return;

	switch (section_type) {
	case 0:           /* 1 Header block */
	        memcpy( (void *) f->data + dif_sequence * 150 * 80, p->data, 480);
	        break;

	case 1:           /* 2 Subcode blocks */
	        memcpy( (void *) f->data + dif_sequence * 150 * 80 + (1 + dif_block) * 80, p->data, 480);
	        break;

	case 2:           /* 3 VAUX blocks */
	        memcpy( (void *) f->data + dif_sequence * 150 * 80 + (3 + dif_block) * 80, p->data, 480);
	        break;

	case 3:           /* 9 Audio blocks interleaved with video */
	        memcpy( (void *) f->data + dif_sequence * 150 * 80 + (6 + dif_block * 16) * 80, p->data, 480);
	        break;

	case 4:           /* 135 Video blocks interleaved with audio */
	        memcpy( (void *) f->data + dif_sequence * 150 * 80 + (7 + (dif_block / 15) + dif_block) * 80, p->data, 480);
	        break;

	default:           /* we can not handle any other data */
	        break;
	}
}