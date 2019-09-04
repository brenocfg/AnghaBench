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
struct sockopt {scalar_t__ sopt_dir; int sopt_name; int /*<<< orphan*/  sopt_p; } ;
struct dn_pipe {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
#define  IP_DUMMYNET_CONFIGURE 131 
#define  IP_DUMMYNET_DEL 130 
#define  IP_DUMMYNET_FLUSH 129 
#define  IP_DUMMYNET_GET 128 
 scalar_t__ SOPT_SET ; 
 int config_pipe (struct dn_pipe*) ; 
 int cp_pipe_from_user_32 (struct sockopt*,struct dn_pipe*) ; 
 int cp_pipe_from_user_64 (struct sockopt*,struct dn_pipe*) ; 
 int delete_pipe (struct dn_pipe*) ; 
 int /*<<< orphan*/  dummynet_flush () ; 
 int dummynet_get (struct sockopt*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  proc_is64bit (int /*<<< orphan*/ ) ; 
 int securelevel ; 

__attribute__((used)) static int
ip_dn_ctl(struct sockopt *sopt)
{
    int error = 0 ;
    struct dn_pipe *p, tmp_pipe;

    /* Disallow sets in really-really secure mode. */
    if (sopt->sopt_dir == SOPT_SET && securelevel >= 3)
	return (EPERM);

    switch (sopt->sopt_name) {
    default :
	printf("dummynet: -- unknown option %d", sopt->sopt_name);
	return EINVAL ;

    case IP_DUMMYNET_GET :
	error = dummynet_get(sopt);
	break ;

    case IP_DUMMYNET_FLUSH :
	dummynet_flush() ;
	break ;

    case IP_DUMMYNET_CONFIGURE :
	p = &tmp_pipe ;
	if (proc_is64bit(sopt->sopt_p))
		error = cp_pipe_from_user_64( sopt, p );
	else
		error = cp_pipe_from_user_32( sopt, p );

	if (error)
	    break ;
	error = config_pipe(p);
	break ;

    case IP_DUMMYNET_DEL :	/* remove a pipe or queue */
	p = &tmp_pipe ;
	if (proc_is64bit(sopt->sopt_p))
		error = cp_pipe_from_user_64( sopt, p );
	else
		error = cp_pipe_from_user_32( sopt, p );
	if (error)
	    break ;

	error = delete_pipe(p);
	break ;
    }
    return error ;
}