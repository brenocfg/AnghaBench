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
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int u_int32_t ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  USER_ADDR_NULL ; 
 int* _MALLOC (int,int /*<<< orphan*/ ,int) ; 
 int copyout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_free_protolist (int*) ; 
 int if_get_protolist (struct ifnet*,int*,int) ; 

__attribute__((used)) static int
ifioctl_get_protolist(struct ifnet *ifp, u_int32_t * ret_count,
    user_addr_t ifpl)
{
	u_int32_t	actual_count;
	u_int32_t	count;
	int		error = 0;
	u_int32_t	*list = NULL;

	/* find out how many */
	count = if_get_protolist(ifp, NULL, 0);
	if (ifpl == USER_ADDR_NULL) {
		goto done;
	}

	/* copy out how many there's space for */
	if (*ret_count < count) {
		count = *ret_count;
	}
	if (count == 0) {
		goto done;
	}
	list = _MALLOC(count * sizeof(*list), M_TEMP, M_WAITOK | M_ZERO);
	if (list == NULL) {
		error = ENOMEM;
		goto done;
	}
	actual_count = if_get_protolist(ifp, list, count);
	if (actual_count < count) {
		count = actual_count;
	}
	if (count != 0) {
		error = copyout((caddr_t)list, ifpl, count * sizeof(*list));
	}

 done:
	if (list != NULL) {
		if_free_protolist(list);
	}
	*ret_count = count;
	return (error);
}