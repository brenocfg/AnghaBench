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
struct psmouse_protocol {int type; } ;
typedef  enum psmouse_type { ____Placeholder_psmouse_type } psmouse_type ;

/* Variables and functions */
 int ARRAY_SIZE (struct psmouse_protocol const*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct psmouse_protocol const* psmouse_protocols ; 

__attribute__((used)) static const struct psmouse_protocol *psmouse_protocol_by_type(enum psmouse_type type)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(psmouse_protocols); i++)
		if (psmouse_protocols[i].type == type)
			return &psmouse_protocols[i];

	WARN_ON(1);
	return &psmouse_protocols[0];
}