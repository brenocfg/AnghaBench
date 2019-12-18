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
typedef  int __u8 ;

/* Variables and functions */
 int /*<<< orphan*/ * NCR_700_SBCL_bits ; 
 int /*<<< orphan*/ * NCR_700_SBCL_to_phase ; 
 int /*<<< orphan*/  strcat (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline char *
sbcl_to_string(__u8 sbcl)
{
	int i;
	static char ret[256];

	ret[0]='\0';
	for(i=0; i<8; i++) {
		if((1<<i) & sbcl) 
			strcat(ret, NCR_700_SBCL_bits[i]);
	}
	strcat(ret, NCR_700_SBCL_to_phase[sbcl & 0x07]);
	return ret;
}