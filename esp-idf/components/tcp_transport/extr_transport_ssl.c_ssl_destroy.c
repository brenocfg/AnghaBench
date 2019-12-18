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
typedef  int /*<<< orphan*/  transport_ssl_t ;
typedef  int /*<<< orphan*/  esp_transport_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  esp_transport_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * esp_transport_get_context_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ssl_destroy(esp_transport_handle_t t)
{
    transport_ssl_t *ssl = esp_transport_get_context_data(t);
    esp_transport_close(t);
    free(ssl);
    return 0;
}