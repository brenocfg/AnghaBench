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
struct sockopt {int sopt_level; int sopt_name; int sopt_valsize; int /*<<< orphan*/  sopt_p; int /*<<< orphan*/  sopt_val; int /*<<< orphan*/  sopt_dir; } ;
typedef  int /*<<< orphan*/ * socket_t ;
typedef  int errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAST_USER_ADDR_T (void*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  SOPT_GET ; 
 int /*<<< orphan*/  kernproc ; 
 int sogetoptlock (int /*<<< orphan*/ *,struct sockopt*,int) ; 

errno_t
sock_getsockopt(socket_t sock, int level, int optname, void *optval,
    int	*optlen)
{
	int error = 0;
	struct sockopt	sopt;

	if (sock == NULL || optval == NULL || optlen == NULL)
		return (EINVAL);

	sopt.sopt_dir = SOPT_GET;
	sopt.sopt_level = level;
	sopt.sopt_name = optname;
	sopt.sopt_val = CAST_USER_ADDR_T(optval);
	sopt.sopt_valsize = *optlen;
	sopt.sopt_p = kernproc;
	error = sogetoptlock(sock, &sopt, 1);	/* will lock socket */
	if (error == 0)
		*optlen = sopt.sopt_valsize;
	return (error);
}