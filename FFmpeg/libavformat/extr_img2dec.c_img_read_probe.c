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
struct TYPE_3__ {scalar_t__ buf_size; scalar_t__* filename; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_EXTENSION ; 
 int AVPROBE_SCORE_MAX ; 
 scalar_t__ av_filename_number_test (scalar_t__*) ; 
 scalar_t__ av_match_ext (scalar_t__*,char*) ; 
 scalar_t__ ff_guess_image2_codec (scalar_t__*) ; 
 scalar_t__ is_glob (scalar_t__*) ; 
 size_t strcspn (scalar_t__*,char*) ; 

__attribute__((used)) static int img_read_probe(const AVProbeData *p)
{
    if (p->filename && ff_guess_image2_codec(p->filename)) {
        if (av_filename_number_test(p->filename))
            return AVPROBE_SCORE_MAX;
        else if (is_glob(p->filename))
            return AVPROBE_SCORE_MAX;
        else if (p->filename[strcspn(p->filename, "*?{")]) // probably PT_GLOB
            return AVPROBE_SCORE_EXTENSION + 2; // score chosen to be a tad above the image pipes
        else if (p->buf_size == 0)
            return 0;
        else if (av_match_ext(p->filename, "raw") || av_match_ext(p->filename, "gif"))
            return 5;
        else
            return AVPROBE_SCORE_EXTENSION;
    }
    return 0;
}