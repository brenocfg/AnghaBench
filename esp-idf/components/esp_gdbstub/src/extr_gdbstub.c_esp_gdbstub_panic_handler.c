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
typedef  int /*<<< orphan*/  esp_gdbstub_frame_t ;
struct TYPE_2__ {scalar_t__ state; scalar_t__ paniced_task_index; int /*<<< orphan*/  signal; scalar_t__ current_task_index; int /*<<< orphan*/  regfile; int /*<<< orphan*/  paniced_frame; } ;

/* Variables and functions */
 scalar_t__ GDBSTUB_CUR_TASK_INDEX_UNKNOWN ; 
 scalar_t__ GDBSTUB_NOT_STARTED ; 
 scalar_t__ GDBSTUB_STARTED ; 
 int GDBSTUB_ST_ERR ; 
 scalar_t__ GDBSTUB_TASK_SUPPORT_DISABLED ; 
 int /*<<< orphan*/  esp_gdbstub_frame_to_regfile (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_gdbstub_get_signal (int /*<<< orphan*/ *) ; 
 int esp_gdbstub_handle_command (unsigned char*,size_t) ; 
 int esp_gdbstub_read_command (unsigned char**,size_t*) ; 
 int /*<<< orphan*/  esp_gdbstub_send_end () ; 
 int /*<<< orphan*/  esp_gdbstub_send_str_packet (char*) ; 
 int /*<<< orphan*/  esp_gdbstub_target_init () ; 
 int /*<<< orphan*/  find_paniced_task_index () ; 
 int /*<<< orphan*/  init_task_info () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_1__ s_scratch ; 
 int /*<<< orphan*/  send_reason () ; 

void esp_gdbstub_panic_handler(esp_gdbstub_frame_t *frame)
{
#ifndef CONFIG_ESP_GDBSTUB_SUPPORT_TASKS
    esp_gdbstub_frame_to_regfile(frame, &s_scratch.regfile);
#else
    if (s_scratch.state == GDBSTUB_STARTED) {
        /* We have re-entered GDB Stub. Try disabling task support. */
        s_scratch.state = GDBSTUB_TASK_SUPPORT_DISABLED;
        /* Flush any pending GDB packet (this creates a garbage value) */
        esp_gdbstub_send_end();
    } else if (s_scratch.state == GDBSTUB_NOT_STARTED) {
        s_scratch.state = GDBSTUB_STARTED;
        /* Save the paniced frame and get the list of tasks */
        memcpy(&s_scratch.paniced_frame, frame, sizeof(*frame));
        esp_gdbstub_frame_to_regfile(frame, &s_scratch.regfile);
        init_task_info();
        find_paniced_task_index();
        /* Current task is the paniced task */
        if (s_scratch.paniced_task_index == GDBSTUB_CUR_TASK_INDEX_UNKNOWN) {
            s_scratch.current_task_index = 0;
        }
    }
#endif // CONFIG_ESP_GDBSTUB_SUPPORT_TASKS

    esp_gdbstub_target_init();
    s_scratch.signal = esp_gdbstub_get_signal(frame);
    send_reason();
    while (true) {
        unsigned char *cmd;
        size_t size;
        int res = esp_gdbstub_read_command(&cmd, &size);
        if (res > 0) {
            /* character received instead of a command */
            continue;
        }
        if (res == GDBSTUB_ST_ERR) {
            esp_gdbstub_send_str_packet("E01");
            continue;
        }
        res = esp_gdbstub_handle_command(cmd, size);
        if (res == GDBSTUB_ST_ERR) {
            esp_gdbstub_send_str_packet(NULL);
        }
    }
}