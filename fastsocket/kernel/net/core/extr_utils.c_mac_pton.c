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
typedef  int u8 ;

/* Variables and functions */
 int ETH_ALEN ; 
 int hex_to_bin (char const) ; 
 int /*<<< orphan*/  strchr (char*,char const) ; 
 int strlen (char const*) ; 

int mac_pton(const char *s, u8 *mac)
{
	int i;

	/* XX:XX:XX:XX:XX:XX */
	if (strlen(s) < 3 * ETH_ALEN - 1)
		return 0;

	/* Don't dirty result unless string is valid MAC. */
	for (i = 0; i < ETH_ALEN; i++) {
		if (!strchr("0123456789abcdefABCDEF", s[i * 3]))
			return 0;
		if (!strchr("0123456789abcdefABCDEF", s[i * 3 + 1]))
			return 0;
		if (i != ETH_ALEN - 1 && s[i * 3 + 2] != ':')
			return 0;
	}
	for (i = 0; i < ETH_ALEN; i++) {
		mac[i] = (hex_to_bin(s[i * 3]) << 4) | hex_to_bin(s[i * 3 + 1]);
	}
	return 1;
}