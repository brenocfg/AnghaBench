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
struct socket_smack {char* smk_in; char* smk_out; char* smk_packet; } ;
struct sock {struct socket_smack* sk_security; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 char* current_security () ; 
 struct socket_smack* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smack_sk_alloc_security(struct sock *sk, int family, gfp_t gfp_flags)
{
	char *csp = current_security();
	struct socket_smack *ssp;

	ssp = kzalloc(sizeof(struct socket_smack), gfp_flags);
	if (ssp == NULL)
		return -ENOMEM;

	ssp->smk_in = csp;
	ssp->smk_out = csp;
	ssp->smk_packet[0] = '\0';

	sk->sk_security = ssp;

	return 0;
}