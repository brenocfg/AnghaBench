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
struct super_block {scalar_t__ s_magic; } ;
struct socket_smack {char* smk_in; char* smk_out; } ;
struct socket {TYPE_1__* sk; } ;
struct inode {struct super_block* i_sb; } ;
struct TYPE_2__ {struct socket_smack* sk_security; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct socket* SOCKET_I (struct inode*) ; 
 scalar_t__ SOCKFS_MAGIC ; 
 int /*<<< orphan*/  XATTR_SMACK_IPIN ; 
 int /*<<< orphan*/  XATTR_SMACK_IPOUT ; 
 int /*<<< orphan*/  XATTR_SMACK_SUFFIX ; 
 char* smk_of_inode (struct inode const*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

__attribute__((used)) static int smack_inode_getsecurity(const struct inode *inode,
				   const char *name, void **buffer,
				   bool alloc)
{
	struct socket_smack *ssp;
	struct socket *sock;
	struct super_block *sbp;
	struct inode *ip = (struct inode *)inode;
	char *isp;
	int ilen;
	int rc = 0;

	if (strcmp(name, XATTR_SMACK_SUFFIX) == 0) {
		isp = smk_of_inode(inode);
		ilen = strlen(isp) + 1;
		*buffer = isp;
		return ilen;
	}

	/*
	 * The rest of the Smack xattrs are only on sockets.
	 */
	sbp = ip->i_sb;
	if (sbp->s_magic != SOCKFS_MAGIC)
		return -EOPNOTSUPP;

	sock = SOCKET_I(ip);
	if (sock == NULL || sock->sk == NULL)
		return -EOPNOTSUPP;

	ssp = sock->sk->sk_security;

	if (strcmp(name, XATTR_SMACK_IPIN) == 0)
		isp = ssp->smk_in;
	else if (strcmp(name, XATTR_SMACK_IPOUT) == 0)
		isp = ssp->smk_out;
	else
		return -EOPNOTSUPP;

	ilen = strlen(isp) + 1;
	if (rc == 0) {
		*buffer = isp;
		rc = ilen;
	}

	return rc;
}