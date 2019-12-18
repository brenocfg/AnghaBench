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
typedef  int u_int8_t ;
struct tcphdr {int doff; } ;
struct sk_buff {int dummy; } ;
struct ip_ct_tcp_state {int td_scale; int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int IP_CT_TCP_FLAG_SACK_PERM ; 
 int IP_CT_TCP_FLAG_WINDOW_SCALE ; 
 int TCPOLEN_SACK_PERM ; 
 int TCPOLEN_WINDOW ; 
#define  TCPOPT_EOL 129 
#define  TCPOPT_NOP 128 
 int TCPOPT_SACK_PERM ; 
 int TCPOPT_WINDOW ; 
 unsigned char* skb_header_pointer (struct sk_buff const*,unsigned int,int,unsigned char*) ; 

__attribute__((used)) static void tcp_options(const struct sk_buff *skb,
			unsigned int dataoff,
			const struct tcphdr *tcph,
			struct ip_ct_tcp_state *state)
{
	unsigned char buff[(15 * 4) - sizeof(struct tcphdr)];
	const unsigned char *ptr;
	int length = (tcph->doff*4) - sizeof(struct tcphdr);

	if (!length)
		return;

	ptr = skb_header_pointer(skb, dataoff + sizeof(struct tcphdr),
				 length, buff);
	BUG_ON(ptr == NULL);

	state->td_scale =
	state->flags = 0;

	while (length > 0) {
		int opcode=*ptr++;
		int opsize;

		switch (opcode) {
		case TCPOPT_EOL:
			return;
		case TCPOPT_NOP:	/* Ref: RFC 793 section 3.1 */
			length--;
			continue;
		default:
			opsize=*ptr++;
			if (opsize < 2) /* "silly options" */
				return;
			if (opsize > length)
				break;	/* don't parse partial options */

			if (opcode == TCPOPT_SACK_PERM
			    && opsize == TCPOLEN_SACK_PERM)
				state->flags |= IP_CT_TCP_FLAG_SACK_PERM;
			else if (opcode == TCPOPT_WINDOW
				 && opsize == TCPOLEN_WINDOW) {
				state->td_scale = *(u_int8_t *)ptr;

				if (state->td_scale > 14) {
					/* See RFC1323 */
					state->td_scale = 14;
				}
				state->flags |=
					IP_CT_TCP_FLAG_WINDOW_SCALE;
			}
			ptr += opsize - 2;
			length -= opsize;
		}
	}
}