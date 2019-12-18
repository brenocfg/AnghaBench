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
typedef  int /*<<< orphan*/  u8_t ;
struct pbuf {int /*<<< orphan*/  len; struct ip_hdr* payload; } ;
struct ip_hdr {int /*<<< orphan*/  src; scalar_t__ chksum; } ;
struct icmp_dur_hdr {int /*<<< orphan*/  src; scalar_t__ chksum; } ;
typedef  enum icmp_dur_type { ____Placeholder_icmp_dur_type } icmp_dur_type ;
struct TYPE_2__ {int /*<<< orphan*/  xmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICMPH_CODE_SET (struct ip_hdr*,int) ; 
 int /*<<< orphan*/  ICMPH_TYPE_SET (struct ip_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICMP_DUR ; 
 int /*<<< orphan*/  ICMP_STATS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICMP_TTL ; 
 scalar_t__ IP_HLEN ; 
 int /*<<< orphan*/  IP_PROTO_ICMP ; 
 int /*<<< orphan*/  PBUF_IP ; 
 int /*<<< orphan*/  PBUF_RAM ; 
 TYPE_1__ icmp ; 
 scalar_t__ inet_chksum (struct ip_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_output (struct pbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct ip_hdr*,scalar_t__) ; 
 struct pbuf* pbuf_alloc (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pbuf_free (struct pbuf*) ; 
 int /*<<< orphan*/  snmp_inc_icmpoutdestunreachs () ; 
 int /*<<< orphan*/  snmp_inc_icmpoutmsgs () ; 

void
icmp_dest_unreach(struct pbuf *p, enum icmp_dur_type t)
{
  struct pbuf *q;
  struct ip_hdr *iphdr;
  struct icmp_dur_hdr *idur;

  q = pbuf_alloc(PBUF_IP, 8 + IP_HLEN + 8, PBUF_RAM);
  /* ICMP header + IP header + 8 bytes of data */

  iphdr = p->payload;

  idur = q->payload;
  ICMPH_TYPE_SET(idur, ICMP_DUR);
  ICMPH_CODE_SET(idur, t);

  memcpy((u8_t *)q->payload + 8, p->payload, IP_HLEN + 8);

  /* calculate checksum */
  idur->chksum = 0;
  idur->chksum = inet_chksum(idur, q->len);
  ICMP_STATS_INC(icmp.xmit);
  /* increase number of messages attempted to send */
  snmp_inc_icmpoutmsgs();
  /* increase number of destination unreachable messages attempted to send */
  snmp_inc_icmpoutdestunreachs();

  ip_output(q, NULL, &(iphdr->src),
	    ICMP_TTL, 0, IP_PROTO_ICMP);
  pbuf_free(q);
}