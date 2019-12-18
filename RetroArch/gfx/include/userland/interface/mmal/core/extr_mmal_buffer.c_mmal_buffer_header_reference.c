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
struct TYPE_6__ {TYPE_1__* priv; } ;
struct TYPE_5__ {TYPE_2__* reference; } ;
typedef  TYPE_2__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */

MMAL_BUFFER_HEADER_T *mmal_buffer_header_reference(MMAL_BUFFER_HEADER_T *header)
{
   return header->priv->reference;
}