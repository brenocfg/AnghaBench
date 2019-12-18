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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ DCCPF_ACK_RATIO ; 
 scalar_t__ DCCPF_SEQUENCE_WINDOW ; 

__attribute__((used)) static u8 dccp_feat_valid_nn_length(u8 feat_num)
{
	if (feat_num == DCCPF_ACK_RATIO)	/* RFC 4340, 11.3 and 6.6.8 */
		return 2;
	if (feat_num == DCCPF_SEQUENCE_WINDOW)	/* RFC 4340, 7.5.2 and 6.5  */
		return 6;
	return 0;
}