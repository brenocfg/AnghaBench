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
struct dmi_header {int type; int length; } ;

/* Variables and functions */
 int dell_new_hk_type ; 
 int /*<<< orphan*/  setup_new_hk_map (struct dmi_header const*) ; 

__attribute__((used)) static void find_hk_type(const struct dmi_header *dm, void *dummy)
{

	if ((dm->type == 0xb2) && (dm->length > 6)) {
		dell_new_hk_type = true;
		setup_new_hk_map(dm);
	}

}