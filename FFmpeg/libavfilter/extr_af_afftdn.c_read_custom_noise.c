#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  band_noise ;
struct TYPE_6__ {int /*<<< orphan*/  band_noise_str; TYPE_1__* dnch; } ;
struct TYPE_5__ {int /*<<< orphan*/  band_noise; } ;
typedef  TYPE_1__ DeNoiseChannel ;
typedef  TYPE_2__ AudioFFTDeNoiseContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int av_clip (int,int,int) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int av_sscanf (char*,char*,int*) ; 
 char* av_strdup (int /*<<< orphan*/ ) ; 
 char* av_strtok (char*,char*,char**) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void read_custom_noise(AudioFFTDeNoiseContext *s, int ch)
{
    DeNoiseChannel *dnch = &s->dnch[ch];
    char *p, *arg, *saveptr = NULL;
    int i, ret, band_noise[15] = { 0 };

    if (!s->band_noise_str)
        return;

    p = av_strdup(s->band_noise_str);
    if (!p)
        return;

    for (i = 0; i < 15; i++) {
        if (!(arg = av_strtok(p, "| ", &saveptr)))
            break;

        p = NULL;

        ret = av_sscanf(arg, "%d", &band_noise[i]);
        if (ret != 1) {
            av_log(s, AV_LOG_ERROR, "Custom band noise must be integer.\n");
            break;
        }

        band_noise[i] = av_clip(band_noise[i], -24, 24);
    }

    av_free(p);
    memcpy(dnch->band_noise, band_noise, sizeof(band_noise));
}