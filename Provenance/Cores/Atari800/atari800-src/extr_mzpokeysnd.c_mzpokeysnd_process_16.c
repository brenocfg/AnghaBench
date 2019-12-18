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
typedef  scalar_t__ SWORD ;

/* Variables and functions */
 double MAX_SAMPLE ; 
 double M_PI ; 
 size_t POKEYSND_SAMPBUF_MAX ; 
 int* POKEYSND_sampbuf_cnt ; 
 size_t POKEYSND_sampbuf_ptr ; 
 size_t POKEYSND_sampbuf_rptr ; 
 double* POKEYSND_sampbuf_val ; 
 double POKEYSND_sampout ; 
 double RAND_MAX ; 
 scalar_t__ floor (double) ; 
 double generate_sample (scalar_t__) ; 
 int num_cur_pokeys ; 
 scalar_t__ pokey_states ; 
 double rand () ; 

__attribute__((used)) static void mzpokeysnd_process_16(void* sndbuffer, int sndn)
{
    int i;
    int nsam = sndn;
    SWORD *buffer = (SWORD *) sndbuffer;

    if(num_cur_pokeys<1)
        return; /* module was not initialized */

    /* if there are two pokeys, then the signal is stereo
       we assume even sndn */
    while(nsam >= (int) num_cur_pokeys)
    {
#ifdef VOL_ONLY_SOUND
        if( POKEYSND_sampbuf_rptr!=POKEYSND_sampbuf_ptr )
            { int l;
            if( POKEYSND_sampbuf_cnt[POKEYSND_sampbuf_rptr]>0 )
                POKEYSND_sampbuf_cnt[POKEYSND_sampbuf_rptr]-=1280;
            while(  (l=POKEYSND_sampbuf_cnt[POKEYSND_sampbuf_rptr])<=0 )
                {	POKEYSND_sampout=POKEYSND_sampbuf_val[POKEYSND_sampbuf_rptr];
                        POKEYSND_sampbuf_rptr++;
                        if( POKEYSND_sampbuf_rptr>=POKEYSND_SAMPBUF_MAX )
                                POKEYSND_sampbuf_rptr=0;
                        if( POKEYSND_sampbuf_rptr!=POKEYSND_sampbuf_ptr )
                            {
                            POKEYSND_sampbuf_cnt[POKEYSND_sampbuf_rptr]+=l;
                            }
                        else	break;
                }
            }
#endif
#ifdef VOL_ONLY_SOUND
        buffer[0] = (SWORD)floor((generate_sample(pokey_states) + POKEYSND_sampout - MAX_SAMPLE / 2.0)
         * (65535.0 / MAX_SAMPLE / 4 * M_PI * 0.95) + 0.5 + 0.5 * rand() / RAND_MAX - 0.25);
#else
        buffer[0] = (SWORD)floor((generate_sample(pokey_states) - MAX_SAMPLE / 2.0)
         * (65535.0 / MAX_SAMPLE / 4 * M_PI * 0.95) + 0.5 + 0.5 * rand() / RAND_MAX - 0.25);
#endif
        for(i=1; i<num_cur_pokeys; i++)
        {
            buffer[i] = (SWORD)floor((generate_sample(pokey_states + i) - MAX_SAMPLE / 2.0)
             * (65535.0 / MAX_SAMPLE / 4 * M_PI * 0.95) + 0.5 + 0.5 * rand() / RAND_MAX - 0.25);
        }
        buffer += num_cur_pokeys;
        nsam -= num_cur_pokeys;
    }
}