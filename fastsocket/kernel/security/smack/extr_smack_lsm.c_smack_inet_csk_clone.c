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
struct socket_smack {char* smk_packet; } ;
struct sock {struct socket_smack* sk_security; } ;
struct request_sock {scalar_t__ peer_secid; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMK_MAXLEN ; 
 char* smack_from_secid (scalar_t__) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smack_inet_csk_clone(struct sock *sk,
				 const struct request_sock *req)
{
	struct socket_smack *ssp = sk->sk_security;
	char *smack;

	if (req->peer_secid != 0) {
		smack = smack_from_secid(req->peer_secid);
		strncpy(ssp->smk_packet, smack, SMK_MAXLEN);
	} else
		ssp->smk_packet[0] = '\0';
}