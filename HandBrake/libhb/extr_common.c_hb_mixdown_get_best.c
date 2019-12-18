#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct TYPE_4__ {int amixdown; } ;
typedef  TYPE_1__ hb_mixdown_t ;

/* Variables and functions */
 int HB_ACODEC_PASS_FLAG ; 
 int HB_AMIXDOWN_NONE ; 
 int HB_INVALID_AMIXDOWN ; 
 TYPE_1__* hb_mixdown_get_next (TYPE_1__ const*) ; 
 scalar_t__ hb_mixdown_is_supported (int,int,int /*<<< orphan*/ ) ; 

int hb_mixdown_get_best(uint32_t codec, uint64_t layout, int mixdown)
{
    // Passthru, only "None" mixdown is supported
    if (codec & HB_ACODEC_PASS_FLAG)
        return HB_AMIXDOWN_NONE;

    int best_mixdown                  = HB_INVALID_AMIXDOWN;
    const hb_mixdown_t *audio_mixdown = hb_mixdown_get_next(NULL);
    // test all non-None mixdowns while the value is <= the requested mixdown
    // HB_INVALID_AMIXDOWN means the highest supported mixdown was requested
    while ((audio_mixdown = hb_mixdown_get_next(audio_mixdown)) != NULL)
    {
        if ((mixdown == HB_INVALID_AMIXDOWN || audio_mixdown->amixdown <= mixdown) &&
            (hb_mixdown_is_supported(audio_mixdown->amixdown, codec, layout)))
        {
            best_mixdown = audio_mixdown->amixdown;
        }
    }
    return best_mixdown;
}