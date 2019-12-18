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
typedef  int u_int16_t ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 unsigned int mangle_content_len (struct sk_buff*,char const**,unsigned int*) ; 
 int /*<<< orphan*/  mangle_packet (struct sk_buff*,char const**,unsigned int*,unsigned int,unsigned int,char*,unsigned int) ; 
 unsigned int sprintf (char*,char*,int) ; 

__attribute__((used)) static unsigned int ip_nat_sdp_port(struct sk_buff *skb,
				    const char **dptr,
				    unsigned int *datalen,
				    unsigned int matchoff,
				    unsigned int matchlen,
				    u_int16_t port)
{
	char buffer[sizeof("nnnnn")];
	unsigned int buflen;

	buflen = sprintf(buffer, "%u", port);
	if (!mangle_packet(skb, dptr, datalen, matchoff, matchlen,
			   buffer, buflen))
		return 0;

	return mangle_content_len(skb, dptr, datalen);
}