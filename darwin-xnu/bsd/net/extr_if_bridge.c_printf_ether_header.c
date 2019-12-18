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
struct ether_header {int* ether_shost; int* ether_dhost; int /*<<< orphan*/  ether_type; } ;

/* Variables and functions */
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int,int,int,int,int,int,int,int,int,int) ; 

__attribute__((used)) static void
printf_ether_header(struct ether_header *eh)
{
	printf("%02x:%02x:%02x:%02x:%02x:%02x > "
	    "%02x:%02x:%02x:%02x:%02x:%02x 0x%04x ",
	    eh->ether_shost[0], eh->ether_shost[1], eh->ether_shost[2],
	    eh->ether_shost[3], eh->ether_shost[4], eh->ether_shost[5],
	    eh->ether_dhost[0], eh->ether_dhost[1], eh->ether_dhost[2],
	    eh->ether_dhost[3], eh->ether_dhost[4], eh->ether_dhost[5],
	    ntohs(eh->ether_type));
}