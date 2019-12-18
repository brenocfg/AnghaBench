#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  aqm; } ;

/* Variables and functions */
 TYPE_1__* ap_configuration ; 
 int ap_test_config (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline int ap_test_config_domain(unsigned int domain)
{
	if (!ap_configuration)
		return 1;
	return ap_test_config(ap_configuration->aqm, domain);
}