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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  size_t uint16_t ;
struct sk_buff {int len; } ;
struct sadb_msg {int dummy; } ;
struct sadb_ext {int sadb_ext_len; size_t sadb_ext_type; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t SADB_EXT_ADDRESS_DST ; 
 size_t SADB_EXT_ADDRESS_PROXY ; 
 size_t SADB_EXT_ADDRESS_SRC ; 
 size_t SADB_EXT_MAX ; 
 size_t SADB_EXT_RESERVED ; 
 size_t SADB_X_EXT_NAT_T_OA ; 
 size_t SADB_X_EXT_SEC_CTX ; 
 scalar_t__* sadb_ext_min_len ; 
 scalar_t__ verify_address_len (char*) ; 
 scalar_t__ verify_sec_ctx_len (char*) ; 

__attribute__((used)) static int parse_exthdrs(struct sk_buff *skb, struct sadb_msg *hdr, void **ext_hdrs)
{
	char *p = (char *) hdr;
	int len = skb->len;

	len -= sizeof(*hdr);
	p += sizeof(*hdr);
	while (len > 0) {
		struct sadb_ext *ehdr = (struct sadb_ext *) p;
		uint16_t ext_type;
		int ext_len;

		ext_len  = ehdr->sadb_ext_len;
		ext_len *= sizeof(uint64_t);
		ext_type = ehdr->sadb_ext_type;
		if (ext_len < sizeof(uint64_t) ||
		    ext_len > len ||
		    ext_type == SADB_EXT_RESERVED)
			return -EINVAL;

		if (ext_type <= SADB_EXT_MAX) {
			int min = (int) sadb_ext_min_len[ext_type];
			if (ext_len < min)
				return -EINVAL;
			if (ext_hdrs[ext_type-1] != NULL)
				return -EINVAL;
			if (ext_type == SADB_EXT_ADDRESS_SRC ||
			    ext_type == SADB_EXT_ADDRESS_DST ||
			    ext_type == SADB_EXT_ADDRESS_PROXY ||
			    ext_type == SADB_X_EXT_NAT_T_OA) {
				if (verify_address_len(p))
					return -EINVAL;
			}
			if (ext_type == SADB_X_EXT_SEC_CTX) {
				if (verify_sec_ctx_len(p))
					return -EINVAL;
			}
			ext_hdrs[ext_type-1] = p;
		}
		p   += ext_len;
		len -= ext_len;
	}

	return 0;
}