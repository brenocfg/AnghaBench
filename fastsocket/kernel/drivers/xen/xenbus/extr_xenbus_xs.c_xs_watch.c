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
struct kvec {void* iov_len; void* iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct kvec*) ; 
 int /*<<< orphan*/  XBT_NIL ; 
 int /*<<< orphan*/  XS_WATCH ; 
 void* strlen (char const*) ; 
 int xs_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xs_talkv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kvec*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int xs_watch(const char *path, const char *token)
{
	struct kvec iov[2];

	iov[0].iov_base = (void *)path;
	iov[0].iov_len = strlen(path) + 1;
	iov[1].iov_base = (void *)token;
	iov[1].iov_len = strlen(token) + 1;

	return xs_error(xs_talkv(XBT_NIL, XS_WATCH, iov,
				 ARRAY_SIZE(iov), NULL));
}