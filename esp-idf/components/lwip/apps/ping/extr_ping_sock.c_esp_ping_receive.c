#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct sockaddr_storage {scalar_t__ ss_family; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int dummy; } ;
struct ip_hdr {int /*<<< orphan*/  _ttl; } ;
struct icmp_echo_hdr {scalar_t__ id; scalar_t__ seqno; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  from ;
struct TYPE_5__ {int /*<<< orphan*/  ttl; int /*<<< orphan*/  received; TYPE_1__* packet_hdr; int /*<<< orphan*/  recv_addr; scalar_t__ recv_len; int /*<<< orphan*/  sock; } ;
typedef  TYPE_2__ esp_ping_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {scalar_t__ id; scalar_t__ seqno; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  IPADDR_TYPE_V4 ; 
 int /*<<< orphan*/  IPADDR_TYPE_V6 ; 
 int IPH_HL (struct ip_hdr*) ; 
 scalar_t__ IP_IS_V4_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IP_SET_TYPE_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet6_addr_to_ip6addr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inet_addr_to_ip4addr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_2_ip4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_2_ip6 (int /*<<< orphan*/ *) ; 
 int recvfrom (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int esp_ping_receive(esp_ping_t *ep)
{
    char buf[64]; // 64 bytes are enough to cover IP header and ICMP header
    int len = 0;
    struct sockaddr_storage from;
    int fromlen = sizeof(from);

    while ((len = recvfrom(ep->sock, buf, sizeof(buf), 0, (struct sockaddr *)&from, (socklen_t *)&fromlen)) > 0) {
        if (len >= (int)(sizeof(struct ip_hdr) + sizeof(struct icmp_echo_hdr))) {
            ep->recv_len = (uint32_t)len;
            if (from.ss_family == AF_INET) {
                // IPv4
                struct sockaddr_in *from4 = (struct sockaddr_in *)&from;
                inet_addr_to_ip4addr(ip_2_ip4(&ep->recv_addr), &from4->sin_addr);
                IP_SET_TYPE_VAL(ep->recv_addr, IPADDR_TYPE_V4);
            } else {
                // IPv6
                struct sockaddr_in6 *from6 = (struct sockaddr_in6 *)&from;
                inet6_addr_to_ip6addr(ip_2_ip6(&ep->recv_addr), &from6->sin6_addr);
                IP_SET_TYPE_VAL(ep->recv_addr, IPADDR_TYPE_V6);
            }

            // Currently we only process IPv4
            if (IP_IS_V4_VAL(ep->recv_addr)) {
                struct ip_hdr *iphdr = (struct ip_hdr *)buf;
                struct icmp_echo_hdr *iecho = (struct icmp_echo_hdr *)(buf + (IPH_HL(iphdr) * 4));
                if ((iecho->id == ep->packet_hdr->id) && (iecho->seqno == ep->packet_hdr->seqno)) {
                    ep->received++;
                    ep->ttl = iphdr->_ttl;
                    return len;
                }
            }
        }
        fromlen = sizeof(from);
    }
    // if timeout, len will be -1
    return len;
}