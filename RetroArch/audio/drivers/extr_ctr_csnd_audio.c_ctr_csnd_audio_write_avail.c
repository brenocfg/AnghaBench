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
struct TYPE_3__ {size_t playpos; size_t pos; } ;
typedef  TYPE_1__ ctr_csnd_audio_t ;

/* Variables and functions */
 size_t CTR_CSND_AUDIO_COUNT_MASK ; 
 int /*<<< orphan*/  ctr_csnd_audio_update_playpos (TYPE_1__*) ; 

__attribute__((used)) static size_t ctr_csnd_audio_write_avail(void *data)
{
   ctr_csnd_audio_t* ctr = (ctr_csnd_audio_t*)data;

   ctr_csnd_audio_update_playpos(ctr);
   return (ctr->playpos - ctr->pos) & CTR_CSND_AUDIO_COUNT_MASK;
}