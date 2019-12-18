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
typedef  int /*<<< orphan*/  u8_t ;
typedef  scalar_t__ u16_t ;
struct pbuf {scalar_t__ len; struct pbuf* next; } ;
struct bd_addr {int dummy; } ;
typedef  scalar_t__ err_t ;

/* Variables and functions */
 scalar_t__ ERR_OK ; 
 int /*<<< orphan*/  L2CAP_ACL_CONT ; 
 int /*<<< orphan*/  L2CAP_ACL_START ; 
 int /*<<< orphan*/  LOG (char*) ; 
 int /*<<< orphan*/  btpbuf_header (struct pbuf*,scalar_t__) ; 
 scalar_t__ lp_acl_write (struct bd_addr*,struct pbuf*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ lp_pdu_maxsize () ; 

err_t l2cap_write(struct bd_addr *bdaddr, struct pbuf *p, u16_t len)
{
	u8_t pb = L2CAP_ACL_START;
	u16_t maxsize;
	u16_t outsize;
	err_t ret = ERR_OK;
	struct pbuf *q;
	u16_t i = 0;

	/*u16_t i;
	struct pbuf *q;
	for(q = p; q != NULL; q = q->next) {
	for(i = 0; i < q->len; ++i) {
	LWIP_DEBUGF(L2CAP_DEBUG, ("l2cap_write: 0x%x\n", ((u8_t *)q->payload)[i]));
	}
	LWIP_DEBUGF(L2CAP_DEBUG, ("l2cap_write: *\n"));
	}
	*/

	maxsize = lp_pdu_maxsize();
	q = p;

	while(len && ret == ERR_OK) {
		//LOG("l2cap_write: len %d maxsize %d p->len %d\n", len, maxsize, p->len);
		if(len > maxsize) {
			ret = lp_acl_write(bdaddr, q, maxsize, pb);
			len -= maxsize;
			outsize = maxsize;
			//LOG("l2cap_write: Outsize before %d\n", outsize);
			while(q->len < outsize) {
				outsize -= q->len;
				q = q->next;
			}
			//LOG("l2cap_write: Outsize after %d\n", outsize);
			if(outsize) {
				btpbuf_header(q, -outsize);
				i += outsize;
			}
			pb = L2CAP_ACL_CONT;
			LOG("l2cap_write: FRAG\n");
		} else {
			ret = lp_acl_write(bdaddr, q, len, pb);
			len = 0;
		}
	}
	btpbuf_header(q, i);
	LOG("l2cap_write: DONE\n");
	return ret;
}