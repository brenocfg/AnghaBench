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
struct android_poll_source {int dummy; } ;
struct android_app {int /*<<< orphan*/  (* onAppCmd ) (struct android_app*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  android_app_post_exec_cmd (struct android_app*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  android_app_pre_exec_cmd (struct android_app*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  android_app_read_cmd (struct android_app*) ; 
 int /*<<< orphan*/  stub1 (struct android_app*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void process_cmd(struct android_app* app, struct android_poll_source* source) {
    int8_t cmd = android_app_read_cmd(app);
    android_app_pre_exec_cmd(app, cmd);
    if (app->onAppCmd != NULL) app->onAppCmd(app, cmd);
    android_app_post_exec_cmd(app, cmd);
}