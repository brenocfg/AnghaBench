#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* pf_release ) (TYPE_2__*) ;scalar_t__ reference; } ;
typedef  TYPE_2__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  mmal_buffer_header_release (scalar_t__) ; 
 int /*<<< orphan*/  mmal_buffer_header_reset (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void mmal_buffer_header_release_continue(MMAL_BUFFER_HEADER_T *header)
{
   mmal_buffer_header_reset(header);
   if (header->priv->reference)
      mmal_buffer_header_release(header->priv->reference);
   header->priv->reference = 0;
   header->priv->pf_release(header);
}