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
struct dccp_ackvec {int av_vec_len; } ;

/* Variables and functions */

__attribute__((used)) static inline int dccp_ackvec_pending(const struct dccp_ackvec *av)
{
	return av->av_vec_len;
}