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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_ext_control {int /*<<< orphan*/  value; int /*<<< orphan*/  id; } ;
struct cx2341x_mpeg_params {int dummy; } ;

/* Variables and functions */
 char** cx2341x_ctrl_get_menu (struct cx2341x_mpeg_params const*,int /*<<< orphan*/ ) ; 
 scalar_t__ cx2341x_get_ctrl (struct cx2341x_mpeg_params const*,struct v4l2_ext_control*) ; 

__attribute__((used)) static const char *cx2341x_menu_item(const struct cx2341x_mpeg_params *p, u32 id)
{
	const char * const *menu = cx2341x_ctrl_get_menu(p, id);
	struct v4l2_ext_control ctrl;

	if (menu == NULL)
		goto invalid;
	ctrl.id = id;
	if (cx2341x_get_ctrl(p, &ctrl))
		goto invalid;
	while (ctrl.value-- && *menu) menu++;
	if (*menu == NULL)
		goto invalid;
	return *menu;

invalid:
	return "<invalid>";
}