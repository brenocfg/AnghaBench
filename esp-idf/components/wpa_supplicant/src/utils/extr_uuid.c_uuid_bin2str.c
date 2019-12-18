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
 int snprintf (char*,size_t,char*,int const,int const,int const,int const,int const,int const,int const,int const,int const,int const,int const,int const,int const,int const,int const,int const) ; 

int uuid_bin2str(const u8 *bin, char *str, size_t max_len)
{
	int len;
	len = snprintf(str, max_len, "%02x%02x%02x%02x-%02x%02x-%02x%02x-"
			  "%02x%02x-%02x%02x%02x%02x%02x%02x",
			  bin[0], bin[1], bin[2], bin[3],
			  bin[4], bin[5], bin[6], bin[7],
			  bin[8], bin[9], bin[10], bin[11],
			  bin[12], bin[13], bin[14], bin[15]);
	if (len < 0 || (size_t) len >= max_len)
		return -1;
	return 0;
}