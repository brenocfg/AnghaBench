#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct CONTEXT_T {int /*<<< orphan*/  semaphore; } ;
struct TYPE_3__ {scalar_t__ user_data; } ;
typedef  TYPE_1__ MMAL_CONNECTION_T ;

/* Variables and functions */
 int /*<<< orphan*/  vcos_semaphore_post (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void connection_callback(MMAL_CONNECTION_T *connection)
{
   struct CONTEXT_T *ctx = (struct CONTEXT_T *)connection->user_data;

   /* The processing is done in our main thread */
   vcos_semaphore_post(&ctx->semaphore);
}