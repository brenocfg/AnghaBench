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
 int /*<<< orphan*/  HCI_INQUIRY_LAP ; 
 int /*<<< orphan*/  btpad_queue_hci_inquiry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * commands ; 
 int inquiry_off ; 
 int /*<<< orphan*/  inquiry_running ; 
 size_t insert_position ; 

__attribute__((used)) static void btpad_set_inquiry_state(bool on)
{
   inquiry_off = !on;

   if (!inquiry_off && !inquiry_running)
      btpad_queue_hci_inquiry(&commands[insert_position],
            HCI_INQUIRY_LAP, 3, 1);
}