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
typedef  int /*<<< orphan*/  packet_fragmenter_t ;

/* Variables and functions */
 int /*<<< orphan*/  controller ; 
 int /*<<< orphan*/  controller_get_interface () ; 
 int /*<<< orphan*/  const interface ; 

const packet_fragmenter_t *packet_fragmenter_get_interface(void)
{
    controller = controller_get_interface();
    return &interface;
}