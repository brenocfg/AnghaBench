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
struct wlp_attr_hdr {void* length; void* type; } ;

/* Variables and functions */
 void* cpu_to_le16 (size_t) ; 

__attribute__((used)) static inline void wlp_set_attr_hdr(struct wlp_attr_hdr *hdr, unsigned type,
				    size_t len)
{
	hdr->type = cpu_to_le16(type);
	hdr->length = cpu_to_le16(len);
}