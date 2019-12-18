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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_PROP_LEN ; 
 int /*<<< orphan*/  PLANETCORE_KEY_SERIAL_BAUD ; 
 void* finddevice (char*) ; 
 int getprop (void*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  planetcore_get_decimal (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 char* prop_buf ; 
 int /*<<< orphan*/  setprop (void*,char*,int /*<<< orphan*/ *,int) ; 

void planetcore_set_serial_speed(const char *table)
{
	void *chosen, *stdout;
	u64 baud;
	u32 baud32;
	int len;

	chosen = finddevice("/chosen");
	if (!chosen)
		return;

	len = getprop(chosen, "linux,stdout-path", prop_buf, MAX_PROP_LEN);
	if (len <= 0)
		return;

	stdout = finddevice(prop_buf);
	if (!stdout) {
		printf("planetcore_set_serial_speed: "
		       "Bad /chosen/linux,stdout-path.\r\n");

		return;
	}

	if (!planetcore_get_decimal(table, PLANETCORE_KEY_SERIAL_BAUD,
	                            &baud)) {
		printf("planetcore_set_serial_speed: No SB tag.\r\n");
		return;
	}

	baud32 = baud;
	setprop(stdout, "current-speed", &baud32, 4);
}