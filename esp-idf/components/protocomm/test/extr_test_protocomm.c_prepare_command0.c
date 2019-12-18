#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  client_pubkey; } ;
typedef  TYPE_2__ session_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_17__ {int /*<<< orphan*/  ver; } ;
struct TYPE_16__ {TYPE_4__* sc0; int /*<<< orphan*/  payload_case; int /*<<< orphan*/  msg; } ;
struct TYPE_12__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_15__ {TYPE_1__ client_pubkey; } ;
struct TYPE_14__ {TYPE_5__* sec1; int /*<<< orphan*/  sec_ver; int /*<<< orphan*/  proto_case; } ;
typedef  TYPE_3__ SessionData ;
typedef  TYPE_4__ SessionCmd0 ;
typedef  TYPE_5__ Sec1Payload ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  PUBLIC_KEY_LEN ; 
 int /*<<< orphan*/  SEC1_MSG_TYPE__Session_Command0 ; 
 int /*<<< orphan*/  SEC1_PAYLOAD__PAYLOAD_SC0 ; 
 int /*<<< orphan*/  SESSION_DATA__PROTO_SEC1 ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  free (TYPE_5__*) ; 
 scalar_t__ malloc (int) ; 
 TYPE_8__ protocomm_security1 ; 
 int /*<<< orphan*/  sec1_payload__init (TYPE_5__*) ; 
 int /*<<< orphan*/  session_cmd0__init (TYPE_4__*) ; 

__attribute__((used)) static esp_err_t prepare_command0(session_t *session, SessionData *req)
{
    Sec1Payload *in = (Sec1Payload *) malloc(sizeof(Sec1Payload));
    if (in == NULL) {
        ESP_LOGE(TAG, "Error allocating memory for request");
        return ESP_ERR_NO_MEM;
    }

    SessionCmd0 *in_req = (SessionCmd0 *) malloc(sizeof(SessionCmd0));
    if (in_req == NULL) {
        ESP_LOGE(TAG, "Error allocating memory for request");
        free(in);
        return ESP_ERR_NO_MEM;
    }

    sec1_payload__init(in);
    session_cmd0__init(in_req);

    in_req->client_pubkey.data = session->client_pubkey;
    in_req->client_pubkey.len = PUBLIC_KEY_LEN;

    in->msg = SEC1_MSG_TYPE__Session_Command0;
    in->payload_case = SEC1_PAYLOAD__PAYLOAD_SC0;
    in->sc0 = in_req;

    req->proto_case = SESSION_DATA__PROTO_SEC1;
    req->sec_ver = protocomm_security1.ver;
    req->sec1 = in;

    return ESP_OK;
}