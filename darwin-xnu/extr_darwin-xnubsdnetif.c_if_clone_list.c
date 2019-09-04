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
struct if_clone {int /*<<< orphan*/  ifc_name; } ;
typedef  int /*<<< orphan*/  outbuf ;

/* Variables and functions */
 int EINVAL ; 
 int IFNAMSIZ ; 
 struct if_clone* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct if_clone* LIST_NEXT (struct if_clone*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USER_ADDR_NULL ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int copyout (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_cloners ; 
 int if_cloners_count ; 
 int /*<<< orphan*/  ifc_list ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
if_clone_list(int count, int *ret_total, user_addr_t dst)
{
	char outbuf[IFNAMSIZ];
	struct if_clone *ifc;
	int error = 0;

	*ret_total = if_cloners_count;
	if (dst == USER_ADDR_NULL) {
		/* Just asking how many there are. */
		return (0);
	}

	if (count < 0)
		return (EINVAL);

	count = (if_cloners_count < count) ? if_cloners_count : count;

	for (ifc = LIST_FIRST(&if_cloners); ifc != NULL && count != 0;
	    ifc = LIST_NEXT(ifc, ifc_list), count--, dst += IFNAMSIZ) {
		bzero(outbuf, sizeof(outbuf));
		strlcpy(outbuf, ifc->ifc_name, IFNAMSIZ);
		error = copyout(outbuf, dst, IFNAMSIZ);
		if (error)
			break;
	}

	return (error);
}