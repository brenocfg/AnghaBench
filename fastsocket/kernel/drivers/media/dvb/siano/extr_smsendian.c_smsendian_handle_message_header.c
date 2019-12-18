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
struct SmsMsgHdr_ST {void* msgFlags; void* msgLength; void* msgType; } ;

/* Variables and functions */
 void* le16_to_cpu (void*) ; 

void smsendian_handle_message_header(void *msg)
{
#ifdef __BIG_ENDIAN
	struct SmsMsgHdr_ST *phdr = (struct SmsMsgHdr_ST *)msg;

	phdr->msgType = le16_to_cpu(phdr->msgType);
	phdr->msgLength = le16_to_cpu(phdr->msgLength);
	phdr->msgFlags = le16_to_cpu(phdr->msgFlags);
#endif /* __BIG_ENDIAN */
}