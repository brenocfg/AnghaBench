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
struct usbip_iso_packet_descriptor {void* actual_length; void* status; void* length; void* offset; } ;

/* Variables and functions */
 void* be32_to_cpu (void*) ; 
 void* cpu_to_be32 (void*) ; 

__attribute__((used)) static void usbip_iso_pakcet_correct_endian(
				struct usbip_iso_packet_descriptor *iso,
				int send)
{
	/* does not need all members. but copy all simply. */
	if (send) {
		iso->offset	= cpu_to_be32(iso->offset);
		iso->length	= cpu_to_be32(iso->length);
		iso->status	= cpu_to_be32(iso->status);
		iso->actual_length = cpu_to_be32(iso->actual_length);
	} else {
		iso->offset	= be32_to_cpu(iso->offset);
		iso->length	= be32_to_cpu(iso->length);
		iso->status	= be32_to_cpu(iso->status);
		iso->actual_length = be32_to_cpu(iso->actual_length);
	}
}