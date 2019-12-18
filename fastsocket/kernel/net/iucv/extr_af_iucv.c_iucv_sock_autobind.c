#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct iucv_sock {scalar_t__ msglimit; int /*<<< orphan*/  src_name; int /*<<< orphan*/ * src_user_id; } ;
typedef  int /*<<< orphan*/  query_buffer ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  autobind_name; } ;

/* Variables and functions */
 int EPROTO ; 
 scalar_t__ IUCV_QUEUELEN_DEFAULT ; 
 scalar_t__ __iucv_get_sock_by_name (char*) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpcmd (char*,char*,int,int*) ; 
 struct iucv_sock* iucv_sk (struct sock*) ; 
 TYPE_1__ iucv_sk_list ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iucv_sock_autobind(struct sock *sk)
{
	struct iucv_sock *iucv = iucv_sk(sk);
	char query_buffer[80];
	char name[12];
	int err = 0;

	/* Set the userid and name */
	cpcmd("QUERY USERID", query_buffer, sizeof(query_buffer), &err);
	if (unlikely(err))
		return -EPROTO;

	memcpy(iucv->src_user_id, query_buffer, 8);

	write_lock_bh(&iucv_sk_list.lock);

	sprintf(name, "%08x", atomic_inc_return(&iucv_sk_list.autobind_name));
	while (__iucv_get_sock_by_name(name)) {
		sprintf(name, "%08x",
			atomic_inc_return(&iucv_sk_list.autobind_name));
	}

	write_unlock_bh(&iucv_sk_list.lock);

	memcpy(&iucv->src_name, name, 8);

	if (!iucv->msglimit)
		iucv->msglimit = IUCV_QUEUELEN_DEFAULT;

	return err;
}