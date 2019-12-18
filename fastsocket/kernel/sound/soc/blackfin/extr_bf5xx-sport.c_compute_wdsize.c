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

/* Variables and functions */
 int WDSIZE_16 ; 
 int WDSIZE_32 ; 
 int WDSIZE_8 ; 

__attribute__((used)) static inline int compute_wdsize(size_t wdsize)
{
	switch (wdsize) {
	case 1:
		return WDSIZE_8;
	case 2:
		return WDSIZE_16;
	case 4:
	default:
		return WDSIZE_32;
	}
}