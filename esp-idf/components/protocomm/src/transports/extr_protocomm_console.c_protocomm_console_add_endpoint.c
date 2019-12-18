#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  protocomm_req_handler_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_4__ {char const* command; char* help; int /*<<< orphan*/  func; } ;
typedef  TYPE_1__ esp_console_cmd_t ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  common_cmd_handler ; 
 int /*<<< orphan*/  esp_console_cmd_register (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static esp_err_t protocomm_console_add_endpoint(const char *ep_name, protocomm_req_handler_t req_handler, void *priv_data)
{
    (void) req_handler;
    (void) priv_data;

    esp_err_t ret;
    esp_console_cmd_t cmd;
    memset(&cmd, 0, sizeof(cmd));

    cmd.command = ep_name;
    cmd.help = "";
    cmd.func = common_cmd_handler;

    ret = esp_console_cmd_register(&cmd);

    return ret;
}