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
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ session_t ;
typedef  scalar_t__ protocomm_security_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  sec1_close_session (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static esp_err_t sec1_cleanup(protocomm_security_handle_t handle)
{
    session_t *cur_session = (session_t *) handle;
    if (cur_session) {
        sec1_close_session(handle, cur_session->id);
    }
    free(handle);
    return ESP_OK;
}