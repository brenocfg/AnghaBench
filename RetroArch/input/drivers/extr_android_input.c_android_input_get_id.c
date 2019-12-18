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
typedef  int /*<<< orphan*/  AInputEvent ;

/* Variables and functions */
 int AInputEvent_getDeviceId (int /*<<< orphan*/ *) ; 
 int pad_id1 ; 
 int pad_id2 ; 

__attribute__((used)) static int android_input_get_id(AInputEvent *event)
{
   int id = AInputEvent_getDeviceId(event);

   if (id == pad_id2)
      id = pad_id1;

   return id;
}