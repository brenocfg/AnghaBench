#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  YuiResolutionClass ;
struct TYPE_3__ {int /*<<< orphan*/  get_property; int /*<<< orphan*/  set_property; } ;
typedef  int /*<<< orphan*/  GParamSpec ;

/* Variables and functions */
 TYPE_1__* G_OBJECT_CLASS (int /*<<< orphan*/ *) ; 
 int G_PARAM_READABLE ; 
 int G_PARAM_WRITABLE ; 
 int /*<<< orphan*/  PROP_GROUP ; 
 int /*<<< orphan*/  PROP_KEYFILE ; 
 int /*<<< orphan*/  g_object_class_install_property (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_param_spec_pointer (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  yui_resolution_get_property ; 
 int /*<<< orphan*/  yui_resolution_set_property ; 

__attribute__((used)) static void yui_resolution_class_init (YuiResolutionClass *klass) {
	GParamSpec * param;

	G_OBJECT_CLASS(klass)->set_property = yui_resolution_set_property;
	G_OBJECT_CLASS(klass)->get_property = yui_resolution_get_property;

	param = g_param_spec_pointer("key-file", 0, 0, G_PARAM_READABLE | G_PARAM_WRITABLE);
	g_object_class_install_property(G_OBJECT_CLASS(klass), PROP_KEYFILE, param);

	param = g_param_spec_pointer("group", 0, 0, G_PARAM_READABLE | G_PARAM_WRITABLE);
	g_object_class_install_property(G_OBJECT_CLASS(klass), PROP_GROUP, param);
}