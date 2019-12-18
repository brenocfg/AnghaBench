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
struct qmi_msg {unsigned char* tlv; int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,void const*,unsigned int) ; 

int qmi_add_tlv(struct qmi_msg *msg,
		unsigned type, unsigned size, const void *data)
{
	unsigned char *x = msg->tlv + msg->size;

	x[0] = type;
	x[1] = size;
	x[2] = size >> 8;

	memcpy(x + 3, data, size);

	msg->size += (size + 3);

	return 0;
}