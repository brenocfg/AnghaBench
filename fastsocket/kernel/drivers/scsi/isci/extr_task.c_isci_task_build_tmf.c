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
struct isci_tmf {int tmf_code; } ;
typedef  enum isci_tmf_function_codes { ____Placeholder_isci_tmf_function_codes } isci_tmf_function_codes ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct isci_tmf*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void isci_task_build_tmf(struct isci_tmf *tmf,
				enum isci_tmf_function_codes code)
{
	memset(tmf, 0, sizeof(*tmf));
	tmf->tmf_code = code;
}