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
struct c_declspecs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  shadow_tag_warned (struct c_declspecs const*,int /*<<< orphan*/ ) ; 

void
shadow_tag (const struct c_declspecs *declspecs)
{
  shadow_tag_warned (declspecs, 0);
}