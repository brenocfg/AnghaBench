#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* i2ChanStrPtr ;
struct TYPE_3__ {int validity; } ;

/* Variables and functions */
 int CHANNEL_MAGIC ; 
 int CHANNEL_MAGIC_BITS ; 
 int CHANNEL_SUPPORT ; 

__attribute__((used)) static inline int
i2Validate ( i2ChanStrPtr pCh )
{
	//ip2trace(pCh->port_index, ITRC_VERIFY,ITRC_ENTER,2,pCh->validity,
	//	(CHANNEL_MAGIC | CHANNEL_SUPPORT));
	return ((pCh->validity & (CHANNEL_MAGIC_BITS | CHANNEL_SUPPORT)) 
			  == (CHANNEL_MAGIC | CHANNEL_SUPPORT));
}