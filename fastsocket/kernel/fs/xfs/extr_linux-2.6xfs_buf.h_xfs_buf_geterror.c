#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int b_error; } ;
typedef  TYPE_1__ xfs_buf_t ;

/* Variables and functions */
 int ENOMEM ; 

__attribute__((used)) static inline int xfs_buf_geterror(xfs_buf_t *bp)
{
	return bp ? bp->b_error : ENOMEM;
}