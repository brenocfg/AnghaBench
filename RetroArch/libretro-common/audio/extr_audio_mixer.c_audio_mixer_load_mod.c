#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_5__ {void* data; int /*<<< orphan*/  size; } ;
struct TYPE_6__ {TYPE_1__ mod; } ;
struct TYPE_7__ {TYPE_2__ types; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ audio_mixer_sound_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_MIXER_TYPE_MOD ; 
 scalar_t__ calloc (int,int) ; 

audio_mixer_sound_t* audio_mixer_load_mod(void *buffer, int32_t size)
{
#ifdef HAVE_IBXM
   audio_mixer_sound_t* sound = (audio_mixer_sound_t*)calloc(1, sizeof(*sound));

   if (!sound)
      return NULL;

   sound->type           = AUDIO_MIXER_TYPE_MOD;
   sound->types.mod.size = size;
   sound->types.mod.data = buffer;

   return sound;
#else
   return NULL;
#endif
}