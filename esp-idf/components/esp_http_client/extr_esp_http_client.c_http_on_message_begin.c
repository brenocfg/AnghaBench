#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* data; } ;
typedef  TYPE_2__ http_parser ;
struct TYPE_7__ {int is_chunk_complete; TYPE_1__* response; } ;
typedef  TYPE_3__ esp_http_client_t ;
struct TYPE_5__ {int is_chunked; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TAG ; 

__attribute__((used)) static int http_on_message_begin(http_parser *parser)
{
    esp_http_client_t *client = parser->data;
    ESP_LOGD(TAG, "on_message_begin");

    client->response->is_chunked = false;
    client->is_chunk_complete = false;
    return 0;
}