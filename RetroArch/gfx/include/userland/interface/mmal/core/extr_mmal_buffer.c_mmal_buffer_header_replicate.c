#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * type; int /*<<< orphan*/  dts; int /*<<< orphan*/  pts; int /*<<< orphan*/  flags; int /*<<< orphan*/  length; int /*<<< orphan*/  offset; int /*<<< orphan*/  data; int /*<<< orphan*/  alloc_size; int /*<<< orphan*/  cmd; TYPE_1__* priv; } ;
struct TYPE_8__ {TYPE_2__* reference; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_TRACE (char*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  MMAL_EINVAL ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  mmal_buffer_header_acquire (TYPE_2__*) ; 

MMAL_STATUS_T mmal_buffer_header_replicate(MMAL_BUFFER_HEADER_T *dest,
   MMAL_BUFFER_HEADER_T *src)
{
#ifdef ENABLE_MMAL_EXTRA_LOGGING
   LOG_TRACE("dest: %p src: %p", dest, src);
#endif

   if (!dest || !src || dest->priv->reference)
      return MMAL_EINVAL;

   mmal_buffer_header_acquire(src);
   dest->priv->reference = src;

   /* Copy all the relevant fields */
   dest->cmd        = src->cmd;
   dest->alloc_size = src->alloc_size;
   dest->data       = src->data;
   dest->offset     = src->offset;
   dest->length     = src->length;
   dest->flags      = src->flags;
   dest->pts        = src->pts;
   dest->dts        = src->dts;
   *dest->type      = *src->type;
   return MMAL_SUCCESS;
}