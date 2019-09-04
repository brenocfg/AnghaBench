#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int FRAC_BITS ; 
 int FRAC_ONE ; 
 int MAX_CHANNELS ; 
 void* atoi (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int int_cos (int) ; 
 int myrnd (unsigned int*,int) ; 
 int /*<<< orphan*/  outfile ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  put16 (int) ; 
 int /*<<< orphan*/  put_wav_header (int,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strrchr (char*,char) ; 

int main(int argc, char **argv)
{
    int i, a, v, j, f, amp, ampa;
    unsigned int seed = 1;
    int tabf1[MAX_CHANNELS], tabf2[MAX_CHANNELS];
    int taba[MAX_CHANNELS];
    int sample_rate = 44100;
    int nb_channels = 2;
    char *ext;

    if (argc < 2 || argc > 5) {
        printf("usage: %s file [<sample rate> [<channels>] [<random seed>]]\n"
               "generate a test raw 16 bit audio stream\n"
               "If the file extension is .wav a WAVE header will be added.\n"
               "default: 44100 Hz stereo\n", argv[0]);
        exit(1);
    }

    if (argc > 2) {
        sample_rate = atoi(argv[2]);
        if (sample_rate <= 0) {
            fprintf(stderr, "invalid sample rate: %d\n", sample_rate);
            return 1;
        }
    }

    if (argc > 3) {
        nb_channels = atoi(argv[3]);
        if (nb_channels < 1 || nb_channels > MAX_CHANNELS) {
            fprintf(stderr, "invalid number of channels: %d\n", nb_channels);
            return 1;
        }
    }

    if (argc > 4)
        seed = atoi(argv[4]);

    outfile = fopen(argv[1], "wb");
    if (!outfile) {
        perror(argv[1]);
        return 1;
    }

    if ((ext = strrchr(argv[1], '.')) && !strcmp(ext, ".wav"))
        put_wav_header(sample_rate, nb_channels, 6 * sample_rate);

    /* 1 second of single freq sine at 1000 Hz */
    a = 0;
    for (i = 0; i < 1 * sample_rate; i++) {
        v = (int_cos(a) * 10000) >> FRAC_BITS;
        for (j = 0; j < nb_channels; j++)
            put16(v);
        a += (1000 * FRAC_ONE) / sample_rate;
    }

    /* 1 second of varying frequency between 100 and 10000 Hz */
    a = 0;
    for (i = 0; i < 1 * sample_rate; i++) {
        v = (int_cos(a) * 10000) >> FRAC_BITS;
        for (j = 0; j < nb_channels; j++)
            put16(v);
        f  = 100 + (((10000 - 100) * i) / sample_rate);
        a += (f * FRAC_ONE) / sample_rate;
    }

    /* 0.5 second of low amplitude white noise */
    for (i = 0; i < sample_rate / 2; i++) {
        v = myrnd(&seed, 20000) - 10000;
        for (j = 0; j < nb_channels; j++)
            put16(v);
    }

    /* 0.5 second of high amplitude white noise */
    for (i = 0; i < sample_rate / 2; i++) {
        v = myrnd(&seed, 65535) - 32768;
        for (j = 0; j < nb_channels; j++)
            put16(v);
    }

    /* 1 second of unrelated ramps for each channel */
    for (j = 0; j < nb_channels; j++) {
        taba[j]  = 0;
        tabf1[j] = 100 + myrnd(&seed, 5000);
        tabf2[j] = 100 + myrnd(&seed, 5000);
    }
    for (i = 0; i < 1 * sample_rate; i++) {
        for (j = 0; j < nb_channels; j++) {
            v = (int_cos(taba[j]) * 10000) >> FRAC_BITS;
            put16(v);
            f        = tabf1[j] + (((tabf2[j] - tabf1[j]) * i) / sample_rate);
            taba[j] += (f * FRAC_ONE) / sample_rate;
        }
    }

    /* 2 seconds of 500 Hz with varying volume */
    a    = 0;
    ampa = 0;
    for (i = 0; i < 2 * sample_rate; i++) {
        for (j = 0; j < nb_channels; j++) {
            amp = ((FRAC_ONE + int_cos(ampa)) * 5000) >> FRAC_BITS;
            if (j & 1)
                amp = 10000 - amp;
            v = (int_cos(a) * amp) >> FRAC_BITS;
            put16(v);
            a    += (500 * FRAC_ONE) / sample_rate;
            ampa += (2 * FRAC_ONE) / sample_rate;
        }
    }

    fclose(outfile);
    return 0;
}