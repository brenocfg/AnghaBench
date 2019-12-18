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
struct bnep_session {struct bnep_proto_filter* proto_filter; } ;
struct bnep_proto_filter {void* end; void* start; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  BNEP_FILTER_LIMIT_REACHED ; 
 int /*<<< orphan*/  BNEP_FILTER_NET_TYPE_RSP ; 
 int /*<<< orphan*/  BNEP_FILTER_UNSUPPORTED_REQ ; 
 int BNEP_MAX_PROTO_FILTERS ; 
 int /*<<< orphan*/  BNEP_SUCCESS ; 
 int /*<<< orphan*/  BT_DBG (char*,int,...) ; 
 int EILSEQ ; 
 int /*<<< orphan*/  bnep_send_rsp (struct bnep_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnep_set_default_proto_filter (struct bnep_session*) ; 
 void* get_unaligned_be16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct bnep_proto_filter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bnep_ctrl_set_netfilter(struct bnep_session *s, __be16 *data, int len)
{
	int n;

	if (len < 2)
		return -EILSEQ;

	n = get_unaligned_be16(data);
	data++; len -= 2;

	if (len < n)
		return -EILSEQ;

	BT_DBG("filter len %d", n);

#ifdef CONFIG_BT_BNEP_PROTO_FILTER
	n /= 4;
	if (n <= BNEP_MAX_PROTO_FILTERS) {
		struct bnep_proto_filter *f = s->proto_filter;
		int i;

		for (i = 0; i < n; i++) {
			f[i].start = get_unaligned_be16(data++);
			f[i].end   = get_unaligned_be16(data++);

			BT_DBG("proto filter start %d end %d",
				f[i].start, f[i].end);
		}

		if (i < BNEP_MAX_PROTO_FILTERS)
			memset(f + i, 0, sizeof(*f));

		if (n == 0)
			bnep_set_default_proto_filter(s);

		bnep_send_rsp(s, BNEP_FILTER_NET_TYPE_RSP, BNEP_SUCCESS);
	} else {
		bnep_send_rsp(s, BNEP_FILTER_NET_TYPE_RSP, BNEP_FILTER_LIMIT_REACHED);
	}
#else
	bnep_send_rsp(s, BNEP_FILTER_NET_TYPE_RSP, BNEP_FILTER_UNSUPPORTED_REQ);
#endif
	return 0;
}