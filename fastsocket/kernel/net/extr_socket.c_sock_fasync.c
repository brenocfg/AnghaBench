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
struct socket {struct sock* sk; struct fasync_struct* fasync_list; } ;
struct sock {int /*<<< orphan*/  sk_callback_lock; } ;
struct file {int /*<<< orphan*/  f_lock; int /*<<< orphan*/  f_flags; struct socket* private_data; } ;
struct fasync_struct {int fa_fd; struct fasync_struct* fa_next; int /*<<< orphan*/  magic; struct file* fa_file; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FASYNC ; 
 int /*<<< orphan*/  FASYNC_MAGIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct fasync_struct*) ; 
 struct fasync_struct* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sock_fasync(int fd, struct file *filp, int on)
{
	struct fasync_struct *fa, *fna = NULL, **prev;
	struct socket *sock;
	struct sock *sk;

	if (on) {
		fna = kmalloc(sizeof(struct fasync_struct), GFP_KERNEL);
		if (fna == NULL)
			return -ENOMEM;
	}

	sock = filp->private_data;

	sk = sock->sk;
	if (sk == NULL) {
		kfree(fna);
		return -EINVAL;
	}

	lock_sock(sk);

	spin_lock(&filp->f_lock);
	if (on)
		filp->f_flags |= FASYNC;
	else
		filp->f_flags &= ~FASYNC;
	spin_unlock(&filp->f_lock);

	prev = &(sock->fasync_list);

	for (fa = *prev; fa != NULL; prev = &fa->fa_next, fa = *prev)
		if (fa->fa_file == filp)
			break;

	if (on) {
		if (fa != NULL) {
			write_lock_bh(&sk->sk_callback_lock);
			fa->fa_fd = fd;
			write_unlock_bh(&sk->sk_callback_lock);

			kfree(fna);
			goto out;
		}
		fna->fa_file = filp;
		fna->fa_fd = fd;
		fna->magic = FASYNC_MAGIC;
		fna->fa_next = sock->fasync_list;
		write_lock_bh(&sk->sk_callback_lock);
		sock->fasync_list = fna;
		write_unlock_bh(&sk->sk_callback_lock);
	} else {
		if (fa != NULL) {
			write_lock_bh(&sk->sk_callback_lock);
			*prev = fa->fa_next;
			write_unlock_bh(&sk->sk_callback_lock);
			kfree(fa);
		}
	}

out:
	release_sock(sock->sk);
	return 0;
}