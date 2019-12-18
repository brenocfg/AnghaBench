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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  dmi_available ; 
 int /*<<< orphan*/  dmi_base ; 
 int /*<<< orphan*/  dmi_len ; 
 int /*<<< orphan*/  dmi_num ; 
 int /*<<< orphan*/  dmi_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void (*) (struct dmi_header const*,void*),void*) ; 
 int /*<<< orphan*/ * ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 

int dmi_walk(void (*decode)(const struct dmi_header *, void *),
	     void *private_data)
{
	u8 *buf;

	if (!dmi_available)
		return -1;

	buf = ioremap(dmi_base, dmi_len);
	if (buf == NULL)
		return -1;

	dmi_table(buf, dmi_len, dmi_num, decode, private_data);

	iounmap(buf);
	return 0;
}