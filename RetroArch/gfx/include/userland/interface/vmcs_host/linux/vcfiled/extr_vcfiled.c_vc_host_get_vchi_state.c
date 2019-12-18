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
typedef  int /*<<< orphan*/  VCHI_INSTANCE_T ;
typedef  int /*<<< orphan*/  VCHI_CONNECTION_T ;

/* Variables and functions */
 int /*<<< orphan*/ * global_connection ; 
 int /*<<< orphan*/  global_initialise_instance ; 

void vc_host_get_vchi_state(VCHI_INSTANCE_T *initialise_instance, VCHI_CONNECTION_T **connection)
{
   *initialise_instance = global_initialise_instance;
   *connection = global_connection;
}