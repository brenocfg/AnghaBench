#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  slot; } ;
typedef  TYPE_1__ ds3_instance_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* get_name ) (TYPE_1__*) ;} ;

/* Variables and functions */
 TYPE_3__ ds3_pad_connection ; 
 int /*<<< orphan*/  input_autoconfigure_disconnect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void ds3_pad_deinit(void *data)
{
   ds3_instance_t *pad = (ds3_instance_t *)data;
   if(pad) {
      input_autoconfigure_disconnect(pad->slot, ds3_pad_connection.get_name(pad));
   }
}