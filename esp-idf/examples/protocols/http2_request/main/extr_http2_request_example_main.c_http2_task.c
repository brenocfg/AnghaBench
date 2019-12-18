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
struct sh2lib_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP2_PUT_PATH ; 
 int /*<<< orphan*/  HTTP2_SERVER_URI ; 
 int /*<<< orphan*/  HTTP2_STREAMING_GET_PATH ; 
 int /*<<< orphan*/  handle_echo_response ; 
 int /*<<< orphan*/  handle_get_response ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  send_put_data ; 
 int /*<<< orphan*/  set_time () ; 
 scalar_t__ sh2lib_connect (struct sh2lib_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh2lib_do_get (struct sh2lib_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh2lib_do_put (struct sh2lib_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sh2lib_execute (struct sh2lib_handle*) ; 
 int /*<<< orphan*/  sh2lib_free (struct sh2lib_handle*) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void http2_task(void *args)
{
    /* Set current time: proper system time is required for TLS based
     * certificate verification.
     */
    set_time();

    /* HTTP2: one connection multiple requests. Do the TLS/TCP connection first */
    printf("Connecting to server\n");
    struct sh2lib_handle hd;
    if (sh2lib_connect(&hd, HTTP2_SERVER_URI) != 0) {
        printf("Failed to connect\n");
        vTaskDelete(NULL);
        return;
    }
    printf("Connection done\n");

    /* HTTP GET  */
    sh2lib_do_get(&hd, HTTP2_STREAMING_GET_PATH, handle_get_response);

    /* HTTP PUT  */
    sh2lib_do_put(&hd, HTTP2_PUT_PATH, send_put_data, handle_echo_response);

    while (1) {
        /* Process HTTP2 send/receive */
        if (sh2lib_execute(&hd) < 0) {
            printf("Error in send/receive\n");
            break;
        }
        vTaskDelay(2);
    }

    sh2lib_free(&hd);
    vTaskDelete(NULL);
}