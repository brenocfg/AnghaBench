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
struct nlattr {int dummy; } ;

/* Variables and functions */
 size_t IPSET_ATTR_PROTOCOL ; 
 scalar_t__ IPSET_PROTOCOL ; 
 scalar_t__ nla_get_u8 (struct nlattr const* const) ; 

__attribute__((used)) static inline bool
protocol_failed(const struct nlattr * const tb[])
{
	return !tb[IPSET_ATTR_PROTOCOL] ||
	       nla_get_u8(tb[IPSET_ATTR_PROTOCOL]) != IPSET_PROTOCOL;
}