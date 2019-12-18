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
struct cftype {scalar_t__ trigger; scalar_t__ write_string; scalar_t__ write_s64; scalar_t__ write_u64; scalar_t__ write; scalar_t__ read_seq_string; scalar_t__ read_map; scalar_t__ read_s64; scalar_t__ read_u64; scalar_t__ read; scalar_t__ mode; } ;
typedef  scalar_t__ mode_t ;

/* Variables and functions */
 scalar_t__ S_IRUGO ; 
 scalar_t__ S_IWUSR ; 

__attribute__((used)) static mode_t cgroup_file_mode(const struct cftype *cft)
{
	mode_t mode = 0;

	if (cft->mode)
		return cft->mode;

	if (cft->read || cft->read_u64 || cft->read_s64 ||
	    cft->read_map || cft->read_seq_string)
		mode |= S_IRUGO;

	if (cft->write || cft->write_u64 || cft->write_s64 ||
	    cft->write_string || cft->trigger)
		mode |= S_IWUSR;

	return mode;
}