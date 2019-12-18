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

/* Variables and functions */
 scalar_t__ cmd ; 
 int /*<<< orphan*/ * db ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int is_connect ; 
 scalar_t__ notify_value_count ; 
 scalar_t__ notify_value_offset ; 
 int /*<<< orphan*/ * notify_value_p ; 
 scalar_t__ spp_conn_id ; 
 int spp_gattc_if ; 
 int spp_mtu_size ; 
 scalar_t__ spp_srv_end_handle ; 
 scalar_t__ spp_srv_start_handle ; 

__attribute__((used)) static void free_gattc_srv_db(void)
{
    is_connect = false;
    spp_gattc_if = 0xff;
    spp_conn_id = 0;
    spp_mtu_size = 23;
    cmd = 0;
    spp_srv_start_handle = 0;
    spp_srv_end_handle = 0;
    notify_value_p = NULL;
    notify_value_offset = 0;
    notify_value_count = 0;
    if(db){
        free(db);
        db = NULL;
    }
}