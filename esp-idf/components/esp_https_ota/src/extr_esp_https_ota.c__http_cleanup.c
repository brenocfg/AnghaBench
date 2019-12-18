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
typedef  int /*<<< orphan*/  esp_http_client_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  esp_http_client_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_http_client_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _http_cleanup(esp_http_client_handle_t client)
{
    esp_http_client_close(client);
    esp_http_client_cleanup(client);
}