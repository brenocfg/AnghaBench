#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* priv; } ;
struct TYPE_7__ {scalar_t__ refcount; int /*<<< orphan*/  pre_release_userdata; scalar_t__ (* pf_pre_release ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_TRACE (char*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  mmal_buffer_header_release_continue (TYPE_2__*) ; 
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

void mmal_buffer_header_release(MMAL_BUFFER_HEADER_T *header)
{
#ifdef ENABLE_MMAL_EXTRA_LOGGING
   LOG_TRACE("%p (%i)", header, (int)header->priv->refcount-1);
#endif

   if(--header->priv->refcount != 0)
      return;

   if (header->priv->pf_pre_release)
   {
      if (header->priv->pf_pre_release(header, header->priv->pre_release_userdata))
         return; /* delay releasing the buffer */
   }
   mmal_buffer_header_release_continue(header);
}