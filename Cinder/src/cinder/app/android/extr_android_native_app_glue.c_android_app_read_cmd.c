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
struct android_app {int /*<<< orphan*/  msgread; } ;
typedef  int int8_t ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
#define  APP_CMD_SAVE_STATE 128 
 int /*<<< orphan*/  LOGE (char*) ; 
 int /*<<< orphan*/  free_saved_state (struct android_app*) ; 
 int read (int /*<<< orphan*/ ,int*,int) ; 

int8_t android_app_read_cmd(struct android_app* android_app) {
    int8_t cmd;
    if (read(android_app->msgread, &cmd, sizeof(cmd)) == sizeof(cmd)) {
        switch (cmd) {
            case APP_CMD_SAVE_STATE:
                free_saved_state(android_app);
                break;
        }
        return cmd;
    } else {
        LOGE("No data on command pipe!");
    }
    return -1;
}