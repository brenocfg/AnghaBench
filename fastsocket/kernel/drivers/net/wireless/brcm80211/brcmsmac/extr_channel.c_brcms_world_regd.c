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
struct brcms_regd {TYPE_1__* regdomain; } ;
struct TYPE_2__ {int /*<<< orphan*/  alpha2; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct brcms_regd*) ; 
 struct brcms_regd* cntry_locales ; 
 int /*<<< orphan*/  strncmp (char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static const struct brcms_regd *brcms_world_regd(const char *regdom, int len)
{
	const struct brcms_regd *regd = NULL;
	int i;

	for (i = 0; i < ARRAY_SIZE(cntry_locales); i++) {
		if (!strncmp(regdom, cntry_locales[i].regdomain->alpha2, len)) {
			regd = &cntry_locales[i];
			break;
		}
	}

	return regd;
}