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
typedef  enum direction { ____Placeholder_direction } direction ;

/* Variables and functions */
 int both ; 
 int load ; 
 int store ; 

__attribute__((used)) static inline enum direction decode_direction(unsigned int insn)
{
	unsigned long tmp = (insn >> 21) & 1;

	if (!tmp)
		return load;
	else {
		switch ((insn>>19)&0xf) {
		case 15: /* swap* */
			return both;
		default:
			return store;
		}
	}
}