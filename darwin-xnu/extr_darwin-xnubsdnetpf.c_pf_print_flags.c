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

/* Variables and functions */
 int TH_ACK ; 
 int TH_CWR ; 
 int TH_ECE ; 
 int TH_FIN ; 
 int TH_PUSH ; 
 int TH_RST ; 
 int TH_SYN ; 
 int TH_URG ; 
 int /*<<< orphan*/  printf (char*) ; 

void
pf_print_flags(u_int8_t f)
{
	if (f)
		printf(" ");
	if (f & TH_FIN)
		printf("F");
	if (f & TH_SYN)
		printf("S");
	if (f & TH_RST)
		printf("R");
	if (f & TH_PUSH)
		printf("P");
	if (f & TH_ACK)
		printf("A");
	if (f & TH_URG)
		printf("U");
	if (f & TH_ECE)
		printf("E");
	if (f & TH_CWR)
		printf("W");
}