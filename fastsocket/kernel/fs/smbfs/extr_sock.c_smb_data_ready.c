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
struct sock {int /*<<< orphan*/  sk_socket; } ;
struct smb_sb_info {void (* data_ready ) (struct sock*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  VERBOSE (char*,struct sock*,int) ; 
 struct smb_sb_info* server_from_socket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smbiod_wake_up () ; 

void
smb_data_ready(struct sock *sk, int len)
{
	struct smb_sb_info *server = server_from_socket(sk->sk_socket);
	void (*data_ready)(struct sock *, int) = server->data_ready;

	data_ready(sk, len);
	VERBOSE("(%p, %d)\n", sk, len);
	smbiod_wake_up();
}