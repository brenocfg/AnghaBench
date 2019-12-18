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
struct bnx2x {int dummy; } ;
typedef  enum sample_bulletin_result { ____Placeholder_sample_bulletin_result } sample_bulletin_result ;

/* Variables and functions */
 int PFVF_BULLETIN_UNCHANGED ; 

__attribute__((used)) static inline enum sample_bulletin_result bnx2x_sample_bulletin(struct bnx2x *bp)
{
	return PFVF_BULLETIN_UNCHANGED;
}