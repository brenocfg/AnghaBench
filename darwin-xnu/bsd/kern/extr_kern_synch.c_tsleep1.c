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
typedef  int /*<<< orphan*/  u_int64_t ;
typedef  int /*<<< orphan*/  lck_mtx_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int _sleep (int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ ,int (*) (int),int /*<<< orphan*/ *) ; 

int
tsleep1(
	void		*chan,
	int		pri,
	const char	*wmsg,
	u_int64_t	abstime,
	int		(*continuation)(int))
{			
	return _sleep((caddr_t)chan, pri, wmsg, abstime, continuation, (lck_mtx_t *)0);
}