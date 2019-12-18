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
struct qmi_msg {unsigned char* tlv; unsigned int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,unsigned char*,unsigned int) ; 

__attribute__((used)) static int qmi_get_tlv(struct qmi_msg *msg,
		       unsigned type, unsigned size, void *data)
{
	unsigned char *x = msg->tlv;
	unsigned len = msg->size;
	unsigned n;

	while (len >= 3) {
		len -= 3;

		/* size of this item */
		n = x[1] | (x[2] << 8);
		if (n > len)
			break;

		if (x[0] == type) {
			if (n != size)
				return -1;
			memcpy(data, x + 3, size);
			return 0;
		}

		x += (n + 3);
		len -= n;
	}

	return -1;
}