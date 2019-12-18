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
typedef  scalar_t__ const u64 ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ dccp_delta_seqno (scalar_t__ const,scalar_t__ const) ; 

__attribute__((used)) static inline bool dccp_loss_free(const u64 s1, const u64 s2, const u64 ndp)
{
	s64 delta = dccp_delta_seqno(s1, s2);

	WARN_ON(delta < 0);
	return (u64)delta <= ndp + 1;
}