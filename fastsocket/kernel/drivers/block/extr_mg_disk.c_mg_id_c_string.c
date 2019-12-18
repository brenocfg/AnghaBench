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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  mg_id_string (int /*<<< orphan*/  const*,unsigned char*,unsigned int,unsigned int) ; 
 int strnlen (unsigned char*,unsigned int) ; 

__attribute__((used)) static void mg_id_c_string(const u16 *id, unsigned char *s,
			   unsigned int ofs, unsigned int len)
{
	unsigned char *p;

	mg_id_string(id, s, ofs, len - 1);

	p = s + strnlen(s, len - 1);
	while (p > s && p[-1] == ' ')
		p--;
	*p = '\0';
}