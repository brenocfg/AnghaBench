#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  slot; } ;
typedef  TYPE_1__ gca_pad_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* get_name ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  input_autoconfigure_disconnect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 TYPE_2__ wiiu_gca_pad_connection ; 

__attribute__((used)) static void wiiu_gca_pad_deinit(void *data)
{
   gca_pad_t *pad = (gca_pad_t *)data;

   if(pad)
   {
      input_autoconfigure_disconnect(pad->slot, wiiu_gca_pad_connection.get_name(pad));
      free(pad);
   }
}