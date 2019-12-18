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
struct xfrm_dst {int dummy; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int xfrm4_init_path(struct xfrm_dst *path, struct dst_entry *dst,
			   int nfheader_len)
{
	return 0;
}