#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* esp_transport_handle_t ;
typedef  int /*<<< orphan*/  esp_tls_last_error_t ;
typedef  int /*<<< orphan*/  esp_tls_error_handle_t ;
struct TYPE_3__ {int /*<<< orphan*/  error_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int) ; 

void esp_transport_set_errors(esp_transport_handle_t t, const esp_tls_error_handle_t error_handle)
{
    if (t)  {
        memcpy(t->error_handle, error_handle, sizeof(esp_tls_last_error_t));
    }
}