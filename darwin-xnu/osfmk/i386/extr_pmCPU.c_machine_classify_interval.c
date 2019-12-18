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
typedef  scalar_t__ uint64_t ;
typedef  size_t uint32_t ;

/* Variables and functions */

__attribute__((used)) static inline void machine_classify_interval(uint64_t interval, uint64_t *bins, uint64_t *binvals, uint32_t nbins) {
	uint32_t i;
 	for (i = 0; i < nbins; i++) {
 		if (interval < binvals[i]) {
 			bins[i]++;
 			break;
 		}
 	}
}