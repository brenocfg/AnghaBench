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
typedef  int u8_t ;
typedef  int u16_t ;
struct uip_tcp_pcb {int mss; } ;

/* Variables and functions */
 int UIP_TCPH_HDRLEN (scalar_t__) ; 
 int UIP_TCP_HLEN ; 
 int UIP_TCP_MSS ; 
 scalar_t__ uip_tcphdr ; 

__attribute__((used)) static void uip_tcp_parseopt(struct uip_tcp_pcb *pcb)
{
	u8_t c;
	u8_t *opts,opt;
	u16_t mss;

	opts = (u8_t*)uip_tcphdr+UIP_TCP_HLEN;
	if(UIP_TCPH_HDRLEN(uip_tcphdr)>0x05) {
		for(c=0;c<((UIP_TCPH_HDRLEN(uip_tcphdr)-5)<<2);) {
			opt = opts[c];
			if(opt==0x00) break;
			else if(opt==0x01) c++;
			else if(opt==0x02 && opts[c+1]==0x04) {
				mss = (opts[c+2]<<8|opts[c+3]);
				pcb->mss = mss>UIP_TCP_MSS?UIP_TCP_MSS:mss;
				break;
			} else {
				if(opts[c+1]==0) break;
				c += opts[c+1];
			}
		}
	}
}