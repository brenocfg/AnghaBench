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
struct ib_ah {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_uverbs_ah_idr ; 
 struct ib_ah* idr_read_obj (int /*<<< orphan*/ *,int,struct ib_ucontext*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ib_ah *idr_read_ah(int ah_handle, struct ib_ucontext *context)
{
	return idr_read_obj(&ib_uverbs_ah_idr, ah_handle, context, 0);
}