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
typedef  int /*<<< orphan*/  MMAL_COMPONENT_T ;

/* Variables and functions */
 scalar_t__ avaudio_do_processing (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void avcodec_do_processing_loop(MMAL_COMPONENT_T *component)
{
   while (avaudio_do_processing(component));
}