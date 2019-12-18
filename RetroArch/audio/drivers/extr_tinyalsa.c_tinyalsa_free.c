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
struct TYPE_3__ {int /*<<< orphan*/ * pcm; } ;
typedef  TYPE_1__ tinyalsa_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  pcm_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tinyalsa_free(void *data)
{
   tinyalsa_t *tinyalsa = (tinyalsa_t*)data;

   if (tinyalsa)
   {
      if (tinyalsa->pcm)
         pcm_close(tinyalsa->pcm);

      tinyalsa->pcm = NULL;
      free(tinyalsa);
   }
}