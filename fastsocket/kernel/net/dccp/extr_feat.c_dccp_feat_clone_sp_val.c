#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_4__ {scalar_t__ len; int /*<<< orphan*/ * vec; } ;
struct TYPE_5__ {TYPE_1__ sp; } ;
typedef  TYPE_2__ dccp_feat_val ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  gfp_any () ; 
 int /*<<< orphan*/ * kmemdup (scalar_t__ const*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dccp_feat_clone_sp_val(dccp_feat_val *fval, u8 const *val, u8 len)
{
	fval->sp.len = len;
	if (fval->sp.len > 0) {
		fval->sp.vec = kmemdup(val, len, gfp_any());
		if (fval->sp.vec == NULL) {
			fval->sp.len = 0;
			return -ENOBUFS;
		}
	}
	return 0;
}