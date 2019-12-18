#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mon_reader_bin {TYPE_1__* b_vec; } ;
struct mon_bin_hdr {int dummy; } ;
struct TYPE_2__ {scalar_t__ ptr; } ;

/* Variables and functions */
 unsigned int CHUNK_SIZE ; 

__attribute__((used)) static inline struct mon_bin_hdr *MON_OFF2HDR(const struct mon_reader_bin *rp,
    unsigned int offset)
{
	return (struct mon_bin_hdr *)
	    (rp->b_vec[offset / CHUNK_SIZE].ptr + offset % CHUNK_SIZE);
}