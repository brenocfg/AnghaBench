#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  word4; void* word3; void* word2; void* word1; } ;
struct TYPE_5__ {int lf; } ;
struct TYPE_4__ {unsigned int fg_off; } ;
union eth1394_hdr {TYPE_3__ words; TYPE_2__ common; TYPE_1__ sf; } ;
struct sk_buff {unsigned int len; } ;

/* Variables and functions */
#define  ETH1394_HDR_LF_FF 129 
 int ETH1394_HDR_LF_IF ; 
 int ETH1394_HDR_LF_LF ; 
#define  ETH1394_HDR_LF_UF 128 
 int* hdr_type_len ; 
 void* htons (void*) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 scalar_t__ skb_pull (struct sk_buff*,unsigned int) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 

__attribute__((used)) static unsigned int ether1394_encapsulate(struct sk_buff *skb,
					  unsigned int max_payload,
					  union eth1394_hdr *hdr)
{
	union eth1394_hdr *bufhdr;
	int ftype = hdr->common.lf;
	int hdrsz = hdr_type_len[ftype];
	unsigned int adj_max_payload = max_payload - hdrsz;

	switch (ftype) {
	case ETH1394_HDR_LF_UF:
		bufhdr = (union eth1394_hdr *)skb_push(skb, hdrsz);
		bufhdr->words.word1 = htons(hdr->words.word1);
		bufhdr->words.word2 = hdr->words.word2;
		break;

	case ETH1394_HDR_LF_FF:
		bufhdr = (union eth1394_hdr *)skb_push(skb, hdrsz);
		bufhdr->words.word1 = htons(hdr->words.word1);
		bufhdr->words.word2 = hdr->words.word2;
		bufhdr->words.word3 = htons(hdr->words.word3);
		bufhdr->words.word4 = 0;

		/* Set frag type here for future interior fragments */
		hdr->common.lf = ETH1394_HDR_LF_IF;
		hdr->sf.fg_off = 0;
		break;

	default:
		hdr->sf.fg_off += adj_max_payload;
		bufhdr = (union eth1394_hdr *)skb_pull(skb, adj_max_payload);
		if (max_payload >= skb->len)
			hdr->common.lf = ETH1394_HDR_LF_LF;
		bufhdr->words.word1 = htons(hdr->words.word1);
		bufhdr->words.word2 = htons(hdr->words.word2);
		bufhdr->words.word3 = htons(hdr->words.word3);
		bufhdr->words.word4 = 0;
	}
	return min(max_payload, skb->len);
}