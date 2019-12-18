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
struct TYPE_5__ {int /*<<< orphan*/  event; } ;
struct TYPE_4__ {scalar_t__ user_data; } ;
typedef  TYPE_1__ MMAL_CONNECTION_T ;
typedef  TYPE_2__ MMALPLAY_T ;

/* Variables and functions */
 int /*<<< orphan*/  vcos_semaphore_post (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mmalplay_connection_cb(MMAL_CONNECTION_T *connection)
{
   MMALPLAY_T *ctx = (MMALPLAY_T *)connection->user_data;
   vcos_semaphore_post(&ctx->event);
}