#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct timeval {int dummy; } ;
struct TYPE_5__ {scalar_t__ seqno; int flags; scalar_t__ count; scalar_t__ sock; struct TYPE_5__* packet_hdr; int /*<<< orphan*/  cb_args; int /*<<< orphan*/  (* on_ping_end ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  interval_ms; int /*<<< orphan*/  (* on_ping_timeout ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* on_ping_success ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ elapsed_time_ms; scalar_t__ total_time_ms; scalar_t__ received; scalar_t__ transmitted; } ;
typedef  TYPE_1__ esp_ping_t ;
typedef  int /*<<< orphan*/  esp_ping_handle_t ;
typedef  int /*<<< orphan*/  TickType_t ;

/* Variables and functions */
 int /*<<< orphan*/  PING_CHECK_START_TIMEOUT_MS ; 
 int PING_FLAGS_INIT ; 
 int PING_FLAGS_START ; 
 scalar_t__ PING_TIME_DIFF_MS (struct timeval,struct timeval) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int esp_ping_receive (TYPE_1__*) ; 
 int /*<<< orphan*/  esp_ping_send (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdMS_TO_TICKS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdTRUE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ulTaskNotifyTake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vTaskDelayUntil (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xTaskGetTickCount () ; 

__attribute__((used)) static void esp_ping_thread(void *args)
{
    esp_ping_t *ep = (esp_ping_t *)(args);
    TickType_t last_wake;
    struct timeval start_time, end_time;
    int recv_ret;

    while (1) {
        /* wait for ping start signal */
        if (ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(PING_CHECK_START_TIMEOUT_MS))) {
            /* initialize runtime statistics */
            ep->packet_hdr->seqno = 0;
            ep->transmitted = 0;
            ep->received = 0;
            ep->total_time_ms = 0;

            last_wake = xTaskGetTickCount();
            while ((ep->flags & PING_FLAGS_START) && ((ep->count == 0) || (ep->packet_hdr->seqno < ep->count))) {
                esp_ping_send(ep);
                gettimeofday(&start_time, NULL);
                recv_ret = esp_ping_receive(ep);
                gettimeofday(&end_time, NULL);
                ep->elapsed_time_ms = PING_TIME_DIFF_MS(end_time, start_time);
                ep->total_time_ms += ep->elapsed_time_ms;
                if (recv_ret >= 0) {
                    if (ep->on_ping_success) {
                        ep->on_ping_success((esp_ping_handle_t)ep, ep->cb_args);
                    }
                } else {
                    if (ep->on_ping_timeout) {
                        ep->on_ping_timeout((esp_ping_handle_t)ep, ep->cb_args);
                    }
                }
                vTaskDelayUntil(&last_wake, pdMS_TO_TICKS(ep->interval_ms)); // to get a more accurate delay
            }
            /* batch of ping operations finished */
            if (ep->on_ping_end) {
                ep->on_ping_end((esp_ping_handle_t)ep, ep->cb_args);
            }
        } else {
            // check if ping has been de-initialized
            if (!(ep->flags & PING_FLAGS_INIT)) {
                break;
            }
        }
    }
    /* before exit task, free all resources */
    if (ep->packet_hdr) {
        free(ep->packet_hdr);
    }
    if (ep->sock > 0) {
        close(ep->sock);
    }
    free(ep);
    vTaskDelete(NULL);
}