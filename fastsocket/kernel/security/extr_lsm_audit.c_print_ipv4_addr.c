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
struct audit_buffer {int dummy; } ;
typedef  scalar_t__ __be32 ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,char*,scalar_t__*) ; 
 scalar_t__* ntohs (scalar_t__) ; 

__attribute__((used)) static inline void print_ipv4_addr(struct audit_buffer *ab, __be32 addr,
				   __be16 port, char *name1, char *name2)
{
	if (addr)
		audit_log_format(ab, " %s=%pI4", name1, &addr);
	if (port)
		audit_log_format(ab, " %s=%d", name2, ntohs(port));
}