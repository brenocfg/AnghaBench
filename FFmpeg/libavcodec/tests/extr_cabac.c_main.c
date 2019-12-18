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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  state ;
typedef  int /*<<< orphan*/  CABACContext ;
typedef  int /*<<< orphan*/  AVLFG ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int SIZE ; 
 int av_lfg_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_lfg_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ff_init_cabac_decoder (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  ff_init_cabac_encoder (int /*<<< orphan*/ *,int*,int) ; 
 int get_cabac_bypass (int /*<<< orphan*/ *) ; 
 int get_cabac_noinline (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  get_cabac_terminate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_cabac (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  put_cabac_bypass (int /*<<< orphan*/ *,int) ; 
 int put_cabac_terminate (int /*<<< orphan*/ *,int) ; 

int main(void){
    CABACContext c;
    uint8_t b[9*SIZE];
    uint8_t r[9*SIZE];
    int i, ret = 0;
    uint8_t state[10]= {0};
    AVLFG prng;

    av_lfg_init(&prng, 1);
    ff_init_cabac_encoder(&c, b, SIZE);

    for(i=0; i<SIZE; i++){
        if(2*i<SIZE) r[i] = av_lfg_get(&prng) % 7;
        else         r[i] = (i>>8)&1;
    }

    for(i=0; i<SIZE; i++){
        put_cabac_bypass(&c, r[i]&1);
    }

    for(i=0; i<SIZE; i++){
        put_cabac(&c, state, r[i]&1);
    }

    i= put_cabac_terminate(&c, 1);
    b[i++] = av_lfg_get(&prng);
    b[i  ] = av_lfg_get(&prng);

    ff_init_cabac_decoder(&c, b, SIZE);

    memset(state, 0, sizeof(state));

    for(i=0; i<SIZE; i++){
        if( (r[i]&1) != get_cabac_bypass(&c) ) {
            av_log(NULL, AV_LOG_ERROR, "CABAC bypass failure at %d\n", i);
            ret = 1;
        }
    }

    for(i=0; i<SIZE; i++){
        if( (r[i]&1) != get_cabac_noinline(&c, state) ) {
            av_log(NULL, AV_LOG_ERROR, "CABAC failure at %d\n", i);
            ret = 1;
        }
    }
    if(!get_cabac_terminate(&c)) {
        av_log(NULL, AV_LOG_ERROR, "where's the Terminator?\n");
        ret = 1;
    }

    return ret;
}