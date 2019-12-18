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
struct output_more_immediate {void** q; } ;

/* Variables and functions */
 int TCODE_ISO_DATA ; 
 void* cpu_to_le32 (unsigned int) ; 

__attribute__((used)) static inline void fill_output_more_immediate(struct output_more_immediate *omi,
					      unsigned char tag,
					      unsigned char channel,
					      unsigned char sync_tag,
					      unsigned int  payload_size)
{
	omi->q[0] = cpu_to_le32(0x02000000 | 8); /* OUTPUT_MORE_IMMEDIATE; 8 is the size of the IT header */
	omi->q[1] = cpu_to_le32(0);
	omi->q[2] = cpu_to_le32(0);
	omi->q[3] = cpu_to_le32(0);

	/* IT packet header */
	omi->q[4] = cpu_to_le32(  (0x0 << 16)  /* IEEE1394_SPEED_100 */
				  | (tag << 14)
				  | (channel << 8)
				  | (TCODE_ISO_DATA << 4)
				  | (sync_tag) );

	/* reserved field; mimic behavior of my Sony DSR-40 */
	omi->q[5] = cpu_to_le32((payload_size << 16) | (0x7F << 8) | 0xA0);

	omi->q[6] = cpu_to_le32(0);
	omi->q[7] = cpu_to_le32(0);
}