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

/* Variables and functions */
 int fls (int) ; 

__attribute__((used)) static u32 be_encoded_q_len(int q_len)
{
	u32 len_encoded = fls(q_len);	/* log2(len) + 1 */
	if (len_encoded == 16)
		len_encoded = 0;
	return len_encoded;
}