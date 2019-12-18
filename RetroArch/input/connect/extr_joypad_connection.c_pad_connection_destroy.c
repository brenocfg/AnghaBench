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
typedef  int /*<<< orphan*/  joypad_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  joypad_is_end_of_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pad_connection_pad_deinit (int /*<<< orphan*/ *,unsigned int) ; 

void pad_connection_destroy(joypad_connection_t *joyconn)
{
   unsigned i;

   for (i = 0; !joypad_is_end_of_list(&joyconn[i]); i ++)
     pad_connection_pad_deinit(&joyconn[i], i);

   free(joyconn);
}