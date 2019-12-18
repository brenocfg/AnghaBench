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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  DST_15BPP ; 
 int /*<<< orphan*/  DST_16BPP ; 
 int /*<<< orphan*/  DST_32BPP ; 
 int /*<<< orphan*/  DST_8BPP ; 

__attribute__((used)) static inline u32 radeon_get_dstbpp(u16 depth)
{
	switch (depth) {
       	case 8:
       		return DST_8BPP;
       	case 15:
       		return DST_15BPP;
       	case 16:
       		return DST_16BPP;
       	case 32:
       		return DST_32BPP;
       	default:
       		return 0;
	}
}