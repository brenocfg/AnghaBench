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
struct TYPE_3__ {struct TYPE_3__* mempool; int /*<<< orphan*/  drv; } ;
typedef  TYPE_1__ libnx_audren_t ;

/* Variables and functions */
 int /*<<< orphan*/  audrenExit () ; 
 int /*<<< orphan*/  audrvClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audrvVoiceStop (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void libnx_audren_audio_free(void *data)
{
   libnx_audren_t *aud = (libnx_audren_t*)data;

   if (!aud)
      return;

   audrvVoiceStop(&aud->drv, 0);
   audrvClose(&aud->drv);
   audrenExit();

   if (aud->mempool)
   {
      free(aud->mempool);
   }

   free(aud);
}