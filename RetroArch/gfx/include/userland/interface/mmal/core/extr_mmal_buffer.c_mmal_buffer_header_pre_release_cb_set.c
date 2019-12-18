#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* priv; } ;
struct TYPE_4__ {void* pre_release_userdata; int /*<<< orphan*/  pf_pre_release; } ;
typedef  TYPE_2__ MMAL_BUFFER_HEADER_T ;
typedef  int /*<<< orphan*/  MMAL_BH_PRE_RELEASE_CB_T ;

/* Variables and functions */

void mmal_buffer_header_pre_release_cb_set(MMAL_BUFFER_HEADER_T *header, MMAL_BH_PRE_RELEASE_CB_T cb, void *userdata)
{
   header->priv->pf_pre_release = cb;
   header->priv->pre_release_userdata = userdata;
}