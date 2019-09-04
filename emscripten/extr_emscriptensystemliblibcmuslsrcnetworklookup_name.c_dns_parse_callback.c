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
struct dpc_ctx {size_t cnt; int /*<<< orphan*/  canon; TYPE_1__* addrs; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  scopeid; int /*<<< orphan*/  family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
#define  RR_A 130 
#define  RR_AAAA 129 
#define  RR_CNAME 128 
 int /*<<< orphan*/  __dn_expand (void const*,unsigned char const*,void const*,char*,int) ; 
 int /*<<< orphan*/  is_valid_hostname (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int dns_parse_callback(void *c, int rr, const void *data, int len, const void *packet)
{
	char tmp[256];
	struct dpc_ctx *ctx = c;
	switch (rr) {
	case RR_A:
		if (len != 4) return -1;
		ctx->addrs[ctx->cnt].family = AF_INET;
		ctx->addrs[ctx->cnt].scopeid = 0;
		memcpy(ctx->addrs[ctx->cnt++].addr, data, 4);
		break;
	case RR_AAAA:
		if (len != 16) return -1;
		ctx->addrs[ctx->cnt].family = AF_INET6;
		ctx->addrs[ctx->cnt].scopeid = 0;
		memcpy(ctx->addrs[ctx->cnt++].addr, data, 16);
		break;
	case RR_CNAME:
		if (__dn_expand(packet, (const unsigned char *)packet + 512,
		    data, tmp, sizeof tmp) > 0 && is_valid_hostname(tmp))
			strcpy(ctx->canon, tmp);
		break;
	}
	return 0;
}