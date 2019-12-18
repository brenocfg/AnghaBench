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
struct cxgbi_tag_format {int rsvd_bits; int rsvd_shift; } ;

/* Variables and functions */

__attribute__((used)) static inline int cxgbi_is_ddp_tag(struct cxgbi_tag_format *tformat, u32 tag)
{
	return !(tag & (1 << (tformat->rsvd_bits + tformat->rsvd_shift - 1)));
}