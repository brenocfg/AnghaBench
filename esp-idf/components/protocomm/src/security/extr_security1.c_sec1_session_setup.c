#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  session_t ;
typedef  int /*<<< orphan*/  protocomm_security_pop_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_10__ {int msg; } ;
struct TYPE_9__ {scalar_t__ sec1; } ;
typedef  TYPE_1__ SessionData ;
typedef  TYPE_2__ Sec1Payload ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
#define  SEC1_MSG_TYPE__Session_Command0 129 
#define  SEC1_MSG_TYPE__Session_Command1 128 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  handle_session_command0 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  handle_session_command1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static esp_err_t sec1_session_setup(session_t *cur_session,
                                    uint32_t session_id,
                                    SessionData *req, SessionData *resp,
                                    const protocomm_security_pop_t *pop)
{
    Sec1Payload *in = (Sec1Payload *) req->sec1;
    esp_err_t ret;

    if (!in) {
        ESP_LOGE(TAG, "Empty session data");
        return ESP_ERR_INVALID_ARG;
    }

    switch (in->msg) {
        case SEC1_MSG_TYPE__Session_Command0:
            ret = handle_session_command0(cur_session, session_id, req, resp, pop);
            break;
        case SEC1_MSG_TYPE__Session_Command1:
            ret = handle_session_command1(cur_session, session_id, req, resp);
            break;
        default:
            ESP_LOGE(TAG, "Invalid security message type");
            ret = ESP_ERR_INVALID_ARG;
    }

    return ret;

}