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
struct TYPE_2__ {void* global_transport_ctx; } ;
struct httpd_data {TYPE_1__ config; } ;
typedef  scalar_t__ httpd_handle_t ;

/* Variables and functions */

void *httpd_get_global_transport_ctx(httpd_handle_t handle)
{
    return ((struct httpd_data *)handle)->config.global_transport_ctx;
}