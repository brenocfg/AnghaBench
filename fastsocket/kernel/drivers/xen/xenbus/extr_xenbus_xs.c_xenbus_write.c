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
struct xenbus_transaction {int dummy; } ;
struct kvec {void* iov_len; void* iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct kvec*) ; 
 scalar_t__ IS_ERR (char const*) ; 
 int PTR_ERR (char const*) ; 
 int /*<<< orphan*/  XS_WRITE ; 
 char* join (char const*,char const*) ; 
 int /*<<< orphan*/  kfree (char const*) ; 
 void* strlen (char const*) ; 
 int xs_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xs_talkv (struct xenbus_transaction,int /*<<< orphan*/ ,struct kvec*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int xenbus_write(struct xenbus_transaction t,
		 const char *dir, const char *node, const char *string)
{
	const char *path;
	struct kvec iovec[2];
	int ret;

	path = join(dir, node);
	if (IS_ERR(path))
		return PTR_ERR(path);

	iovec[0].iov_base = (void *)path;
	iovec[0].iov_len = strlen(path) + 1;
	iovec[1].iov_base = (void *)string;
	iovec[1].iov_len = strlen(string);

	ret = xs_error(xs_talkv(t, XS_WRITE, iovec, ARRAY_SIZE(iovec), NULL));
	kfree(path);
	return ret;
}