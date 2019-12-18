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
struct ip_vs_pe {int dummy; } ;

/* Variables and functions */
 struct ip_vs_pe* __ip_vs_pe_getbyname (char const*) ; 
 int /*<<< orphan*/  request_module (char*,char const*) ; 

struct ip_vs_pe *ip_vs_pe_getbyname(const char *name)
{
	struct ip_vs_pe *pe;

	/* Search for the pe by name */
	pe = __ip_vs_pe_getbyname(name);

	/* If pe not found, load the module and search again */
	if (!pe) {
		request_module("ip_vs_pe_%s", name);
		pe = __ip_vs_pe_getbyname(name);
	}

	return pe;
}