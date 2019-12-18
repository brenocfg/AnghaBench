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
 int SAS_ADDR_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int const) ; 

__attribute__((used)) static inline void asd_stringify_sas_addr(char *p, const u8 *sas_addr)
{
	int i;
	for (i = 0; i < SAS_ADDR_SIZE; i++, p += 2)
		snprintf(p, 3, "%02X", sas_addr[i]);
	*p = '\0';
}