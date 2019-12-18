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
typedef  int UINT ;
typedef  int* PUCHAR ;

/* Variables and functions */

void PacketItoa(UINT n,PUCHAR buf){
int i;

	for(i=0;i<20;i+=2){
		buf[18-i]=(n%10)+48;
		buf[19-i]=0;
		n/=10;
	}

}