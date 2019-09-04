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
struct protoent {char* p_name; char** p_aliases; int /*<<< orphan*/  p_proto; } ;

/* Variables and functions */
 int idx ; 
 int /*<<< orphan*/ * protos ; 
 scalar_t__ strlen (char*) ; 

struct protoent *getprotoent(void)
{
	static struct protoent p;
	static const char *aliases;
	if (idx >= sizeof protos) return NULL;
	p.p_proto = protos[idx];
	p.p_name = (char *)&protos[idx+1];
	p.p_aliases = (char **)&aliases;
	idx += strlen(p.p_name) + 2;
	return &p;
}