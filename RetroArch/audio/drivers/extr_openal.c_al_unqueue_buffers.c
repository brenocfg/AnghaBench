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
struct TYPE_3__ {size_t res_ptr; int /*<<< orphan*/ * res_buf; int /*<<< orphan*/  source; } ;
typedef  TYPE_1__ al_t ;
typedef  scalar_t__ ALint ;

/* Variables and functions */
 int /*<<< orphan*/  AL_BUFFERS_PROCESSED ; 
 int /*<<< orphan*/  alGetSourcei (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  alSourceUnqueueBuffers (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool al_unqueue_buffers(al_t *al)
{
   ALint val;

   alGetSourcei(al->source, AL_BUFFERS_PROCESSED, &val);

   if (val <= 0)
      return false;

   alSourceUnqueueBuffers(al->source, val, &al->res_buf[al->res_ptr]);
   al->res_ptr += val;
   return true;
}