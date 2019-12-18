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
typedef  unsigned long uint8_t ;
typedef  int /*<<< orphan*/  ksign_user_id_actor_t ;
typedef  int /*<<< orphan*/  ksign_signature_actor_t ;
typedef  int /*<<< orphan*/  ksign_public_key_actor_t ;

/* Variables and functions */
 int EBADMSG ; 
#define  PKT_PUBLIC_KEY 130 
#define  PKT_SIGNATURE 129 
#define  PKT_USER_ID 128 
 int ksign_parse_key (unsigned long const*,unsigned long const*,unsigned long*,int,int /*<<< orphan*/ ,void*) ; 
 int ksign_parse_signature (unsigned long const*,unsigned long const*,int /*<<< orphan*/ ,void*) ; 
 int ksign_parse_user_id (unsigned long const*,unsigned long const*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static int ksign_parse_one_packet(const uint8_t **datap,
				  const uint8_t *endp,
				  ksign_signature_actor_t sigfnx,
				  ksign_public_key_actor_t pkfnx,
				  ksign_user_id_actor_t uidfnx,
				  void *data)
{
	int rc, c, ctb, pkttype, lenbytes;
	unsigned long pktlen;
	uint8_t hdr[8];
	int hdrlen;

	/* extract the next packet and dispatch it */
	rc = 0;
	if (*datap >= endp)
		goto leave;
	ctb = *(*datap)++;

	rc = -EBADMSG;

	hdrlen = 0;
	hdr[hdrlen++] = ctb;
	if (!(ctb & 0x80)) {
		printk("ksign: invalid packet (ctb=%02x)\n", ctb);
		goto leave;
	}

	pktlen = 0;
	if (ctb & 0x40) {
		pkttype = ctb & 0x3f;
		if (*datap >= endp) {
			printk("ksign: 1st length byte missing\n");
			goto leave;
		}
		c = *(*datap)++;
		hdr[hdrlen++] = c;

		if (c < 192) {
			pktlen = c;
		} else if (c < 224) {
			pktlen = (c - 192) * 256;
			if (*datap >= endp) {
				printk("ksign: 2nd length byte missing\n");
				goto leave;
			}
			c = *(*datap)++;
			hdr[hdrlen++] = c;
			pktlen += c + 192;
		} else if (c == 255) {
			if (*datap + 3 >= endp) {
				printk("ksign: 4 uint8_t length invalid\n");
				goto leave;
			}
			pktlen  = (hdr[hdrlen++] = *(*datap)++ << 24);
			pktlen |= (hdr[hdrlen++] = *(*datap)++ << 16);
			pktlen |= (hdr[hdrlen++] = *(*datap)++ <<  8);
			pktlen |= (hdr[hdrlen++] = *(*datap)++ <<  0);
		} else {
			pktlen = 0;/* to indicate partial length */
		}
	} else {
		pkttype = (ctb >> 2) & 0xf;
		lenbytes = ((ctb & 3) == 3) ? 0 : (1 << (ctb & 3));
		if( !lenbytes ) {
			pktlen = 0; /* don't know the value */
		} else {
			if (*datap + lenbytes > endp) {
				printk("ksign: length bytes missing\n");
				goto leave;
			}
			for( ; lenbytes; lenbytes-- ) {
				pktlen <<= 8;
				pktlen |= hdr[hdrlen++] = *(*datap)++;
			}
		}
	}

	if (*datap + pktlen > endp) {
		printk("ksign: packet length longer than available data\n");
		goto leave;
	}

	/* deal with the next packet appropriately */
	switch (pkttype) {
	case PKT_PUBLIC_KEY:
		rc = ksign_parse_key(*datap, *datap + pktlen, hdr, hdrlen,
				     pkfnx, data);
		break;
	case PKT_SIGNATURE:
		rc = ksign_parse_signature(*datap, *datap + pktlen,
					   sigfnx, data);
		break;
	case PKT_USER_ID:
		rc = ksign_parse_user_id(*datap, *datap + pktlen,
					 uidfnx, data);
		break;
	default:
		rc = 0; /* unknown packet */
		break;
	}

	*datap += pktlen;
leave:
	return rc;
}