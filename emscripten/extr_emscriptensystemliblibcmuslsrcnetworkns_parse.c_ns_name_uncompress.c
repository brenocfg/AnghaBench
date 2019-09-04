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

/* Variables and functions */
 int /*<<< orphan*/  EMSGSIZE ; 
 int dn_expand (unsigned char const*,unsigned char const*,unsigned char const*,char*,size_t) ; 
 int /*<<< orphan*/  errno ; 

int ns_name_uncompress(const unsigned char *msg, const unsigned char *eom,
                       const unsigned char *src, char *dst, size_t dstsiz)
{
	int r;
	r = dn_expand(msg, eom, src, dst, dstsiz);
	if (r < 0) errno = EMSGSIZE;
	return r;
}