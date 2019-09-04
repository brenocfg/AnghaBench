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
struct ifnamemap {int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; scalar_t__ index; } ;
struct ifnameindexctx {int num; struct ifnamemap* list; scalar_t__ str_bytes; } ;
struct if_nameindex {char* if_name; scalar_t__ if_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  ENOBUFS ; 
 int PTHREAD_CANCEL_DISABLE ; 
 scalar_t__ __rtnetlink_enumerate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifnameindexctx*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct ifnamemap*) ; 
 struct if_nameindex* malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ifnameindexctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netlink_msg_to_nameindex ; 
 int /*<<< orphan*/  pthread_setcancelstate (int,int*) ; 

struct if_nameindex *if_nameindex()
{
	struct ifnameindexctx _ctx, *ctx = &_ctx;
	struct if_nameindex *ifs = 0, *d;
	struct ifnamemap *s;
	char *p;
	int i;
	int cs;

	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &cs);
	memset(ctx, 0, sizeof(*ctx));
	if (__rtnetlink_enumerate(AF_UNSPEC, AF_INET, netlink_msg_to_nameindex, ctx) < 0) goto err;

	ifs = malloc(sizeof(struct if_nameindex[ctx->num+1]) + ctx->str_bytes);
	if (!ifs) goto err;

	p = (char*)(ifs + ctx->num + 1);
	for (i = ctx->num, d = ifs, s = ctx->list; i; i--, s++, d++) {
		d->if_index = s->index;
		d->if_name = p;
		memcpy(p, s->name, s->namelen);
		p += s->namelen;
		*p++ = 0;
	}
	d->if_index = 0;
	d->if_name = 0;
err:
	pthread_setcancelstate(cs, 0);
	free(ctx->list);
	errno = ENOBUFS;
	return ifs;
}