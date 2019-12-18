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
struct TYPE_3__ {int l_logBBsize; } ;
typedef  TYPE_1__ xlog_t ;

/* Variables and functions */

__attribute__((used)) static inline int
xlog_buf_bbcount_valid(
	xlog_t		*log,
	int		bbcount)
{
	return bbcount > 0 && bbcount <= log->l_logBBsize;
}