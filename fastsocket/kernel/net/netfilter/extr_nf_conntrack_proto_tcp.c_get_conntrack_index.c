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
struct tcphdr {scalar_t__ ack; scalar_t__ fin; scalar_t__ syn; scalar_t__ rst; } ;

/* Variables and functions */
 unsigned int TCP_ACK_SET ; 
 unsigned int TCP_FIN_SET ; 
 unsigned int TCP_NONE_SET ; 
 unsigned int TCP_RST_SET ; 
 unsigned int TCP_SYNACK_SET ; 
 unsigned int TCP_SYN_SET ; 

__attribute__((used)) static unsigned int get_conntrack_index(const struct tcphdr *tcph)
{
	if (tcph->rst) return TCP_RST_SET;
	else if (tcph->syn) return (tcph->ack ? TCP_SYNACK_SET : TCP_SYN_SET);
	else if (tcph->fin) return TCP_FIN_SET;
	else if (tcph->ack) return TCP_ACK_SET;
	else return TCP_NONE_SET;
}