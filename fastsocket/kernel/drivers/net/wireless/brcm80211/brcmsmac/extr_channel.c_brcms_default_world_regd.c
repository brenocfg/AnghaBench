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
struct brcms_regd {int dummy; } ;

/* Variables and functions */
 struct brcms_regd const* cntry_locales ; 

__attribute__((used)) static const struct brcms_regd *brcms_default_world_regd(void)
{
	return &cntry_locales[0];
}