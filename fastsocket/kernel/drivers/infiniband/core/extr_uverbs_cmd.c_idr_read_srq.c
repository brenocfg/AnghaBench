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
struct ib_ucontext {int dummy; } ;
struct ib_srq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_uverbs_srq_idr ; 
 struct ib_srq* idr_read_obj (int /*<<< orphan*/ *,int,struct ib_ucontext*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ib_srq *idr_read_srq(int srq_handle, struct ib_ucontext *context)
{
	return idr_read_obj(&ib_uverbs_srq_idr, srq_handle, context, 0);
}