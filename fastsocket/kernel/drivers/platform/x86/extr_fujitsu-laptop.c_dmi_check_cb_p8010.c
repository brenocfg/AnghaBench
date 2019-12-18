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
struct dmi_system_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  keycode4; int /*<<< orphan*/  keycode3; int /*<<< orphan*/  keycode1; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_HELP ; 
 int /*<<< orphan*/  KEY_SWITCHVIDEOMODE ; 
 int /*<<< orphan*/  KEY_WWW ; 
 int /*<<< orphan*/  dmi_check_cb_common (struct dmi_system_id const*) ; 
 TYPE_1__* fujitsu ; 

__attribute__((used)) static int dmi_check_cb_p8010(const struct dmi_system_id *id)
{
	dmi_check_cb_common(id);
	fujitsu->keycode1 = KEY_HELP;	/* "Support" */
	fujitsu->keycode3 = KEY_SWITCHVIDEOMODE;	/* "Presentation" */
	fujitsu->keycode4 = KEY_WWW;	/* "Internet" */
	return 0;
}