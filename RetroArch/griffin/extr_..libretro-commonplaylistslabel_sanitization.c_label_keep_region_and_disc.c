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
 int /*<<< orphan*/  label_sanitize (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  left_parens_or_brackets_excluding_region_or_disc ; 
 int /*<<< orphan*/  right_parens_or_brackets ; 

void label_keep_region_and_disc(char *label)
{
   label_sanitize(label, left_parens_or_brackets_excluding_region_or_disc, right_parens_or_brackets);
}