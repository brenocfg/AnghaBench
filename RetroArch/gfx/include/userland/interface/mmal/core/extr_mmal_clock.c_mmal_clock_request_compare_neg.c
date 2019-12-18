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
struct TYPE_2__ {scalar_t__ media_time_adj; } ;
typedef  int /*<<< orphan*/  MMAL_LIST_ELEMENT_T ;
typedef  TYPE_1__ MMAL_CLOCK_REQUEST_T ;

/* Variables and functions */

__attribute__((used)) static int mmal_clock_request_compare_neg(MMAL_LIST_ELEMENT_T *lhs, MMAL_LIST_ELEMENT_T *rhs)
{
   return ((MMAL_CLOCK_REQUEST_T*)lhs)->media_time_adj > ((MMAL_CLOCK_REQUEST_T*)rhs)->media_time_adj;
}