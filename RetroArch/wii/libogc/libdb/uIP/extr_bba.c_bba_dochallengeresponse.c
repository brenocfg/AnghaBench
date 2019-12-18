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
typedef  int u16 ;
typedef  int /*<<< orphan*/  s8_t ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  UIP_ERR_IF ; 
 int /*<<< orphan*/  UIP_ERR_OK ; 
 int /*<<< orphan*/  UIP_LOG (char*) ; 
 int /*<<< orphan*/  bba_devpoll (int*) ; 

__attribute__((used)) static s8_t bba_dochallengeresponse()
{
	u16 status;
	s32 cnt;

	UIP_LOG("bba_dochallengeresponse()\n");
	/* as we do not have interrupts we've to poll the irqs */
	cnt = 0;
	do {
		cnt++;
		bba_devpoll(&status);
		if(status==0x1000) cnt = 0;
	} while(cnt<100 && !(status&0x0800));

	if(cnt>=1000) return UIP_ERR_IF;
	return UIP_ERR_OK;
}