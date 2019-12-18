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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int /*<<< orphan*/  sprintf (int*,char*,int const) ; 

u32 encode_ie(void *buf, u32 bufsize, const u8 *ie, u32 ielen,
		const u8 *leader, u32 leader_len)
{
	u8 *p;
	u32 i;

	if (bufsize < leader_len)
		return 0;
	p = buf;
	memcpy(p, leader, leader_len);
	bufsize -= leader_len;
	p += leader_len;
	for (i = 0; i < ielen && bufsize > 2; i++)
		p += sprintf(p, "%02x", ie[i]);
	return (i == ielen ? p - (u8 *)buf:0);
}