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
typedef  int u32 ;
struct cxgbi_tag_format {int rsvd_bits; } ;

/* Variables and functions */

__attribute__((used)) static inline int cxgbi_sw_tag_usable(struct cxgbi_tag_format *tformat,
					u32 sw_tag)
{
	sw_tag >>= (32 - tformat->rsvd_bits);
	return !sw_tag;
}