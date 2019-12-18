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
 int /*<<< orphan*/  NETAGENT_DOMAINSIZE ; 
 int /*<<< orphan*/  NETAGENT_TYPESIZE ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
necp_agent_types_match(const char *agent_domain1, const char *agent_type1,
					   const char *agent_domain2, const char *agent_type2)
{
	return ((strlen(agent_domain1) == 0 ||
			 strncmp(agent_domain2, agent_domain1, NETAGENT_DOMAINSIZE) == 0) &&
			(strlen(agent_type1) == 0 ||
			 strncmp(agent_type2, agent_type1, NETAGENT_TYPESIZE) == 0));
}