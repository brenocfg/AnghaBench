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
typedef  int uint8_t ;
typedef  TYPE_1__* gss_buffer_t ;
struct TYPE_3__ {int length; scalar_t__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

void
printgbuf(const char *str, gss_buffer_t buf)
{
	size_t i;
	size_t len = buf->length > 128 ? 128 : buf->length;

	printf("%s:   len = %d value = %p\n", str ? str : "buffer", (int)buf->length, buf->value);
	for (i = 0; i < len; i++)  {
		const char *s = ((i + 1) % 8) ? " " : ((i + 1) % 16) ? "    " : "\n";
		printf("%02x%s", ((uint8_t *)buf->value)[i], s);
	}
	if (i % 16)
		printf("\n");
}