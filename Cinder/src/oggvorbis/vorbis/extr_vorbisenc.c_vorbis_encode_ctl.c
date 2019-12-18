#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {double rate; int channels; TYPE_3__* codec_setup; } ;
typedef  TYPE_1__ vorbis_info ;
struct ovectl_ratemanage_arg {double bitrate_hard_window; double bitrate_av_window; int bitrate_av_window_center; double bitrate_hard_min; double bitrate_hard_max; double bitrate_av_lo; double bitrate_av_hi; int /*<<< orphan*/  management_active; } ;
struct ovectl_ratemanage2_arg {int bitrate_limit_min_kbps; int bitrate_limit_max_kbps; int bitrate_average_kbps; int bitrate_average_damping; int bitrate_limit_reservoir_bits; int bitrate_limit_reservoir_bias; int /*<<< orphan*/  management_active; } ;
struct TYPE_7__ {double bitrate_reservoir; double bitrate_min; double bitrate_max; double bitrate_av; int bitrate_av_damp; int bitrate_reservoir_bias; double lowpass_kHz; int lowpass_altered; double impulse_noisetune; int coupling_p; double base_setting; void const* setup; int /*<<< orphan*/  managed; int /*<<< orphan*/  req; scalar_t__ set_in_stone; } ;
typedef  TYPE_2__ highlevel_encode_setup ;
struct TYPE_8__ {TYPE_2__ hi; } ;
typedef  TYPE_3__ codec_setup_info ;

/* Variables and functions */
#define  OV_ECTL_COUPLING_GET 139 
#define  OV_ECTL_COUPLING_SET 138 
#define  OV_ECTL_IBLOCK_GET 137 
#define  OV_ECTL_IBLOCK_SET 136 
#define  OV_ECTL_LOWPASS_GET 135 
#define  OV_ECTL_LOWPASS_SET 134 
#define  OV_ECTL_RATEMANAGE2_GET 133 
#define  OV_ECTL_RATEMANAGE2_SET 132 
#define  OV_ECTL_RATEMANAGE_AVG 131 
#define  OV_ECTL_RATEMANAGE_GET 130 
#define  OV_ECTL_RATEMANAGE_HARD 129 
#define  OV_ECTL_RATEMANAGE_SET 128 
 int OV_EIMPL ; 
 int OV_EINVAL ; 
 void* get_setup_template (int,double,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double*) ; 
 int /*<<< orphan*/  vorbis_encode_setup_setting (TYPE_1__*,int,double) ; 

int vorbis_encode_ctl(vorbis_info *vi,int number,void *arg){
  if(vi){
    codec_setup_info *ci=vi->codec_setup;
    highlevel_encode_setup *hi=&ci->hi;
    int setp=(number&0xf); /* a read request has a low nibble of 0 */

    if(setp && hi->set_in_stone)return(OV_EINVAL);

    switch(number){

    /* now deprecated *****************/
    case OV_ECTL_RATEMANAGE_GET:
      {

        struct ovectl_ratemanage_arg *ai=
          (struct ovectl_ratemanage_arg *)arg;

        ai->management_active=hi->managed;
        ai->bitrate_hard_window=ai->bitrate_av_window=
          (double)hi->bitrate_reservoir/vi->rate;
        ai->bitrate_av_window_center=1.;
        ai->bitrate_hard_min=hi->bitrate_min;
        ai->bitrate_hard_max=hi->bitrate_max;
        ai->bitrate_av_lo=hi->bitrate_av;
        ai->bitrate_av_hi=hi->bitrate_av;

      }
      return(0);

    /* now deprecated *****************/
    case OV_ECTL_RATEMANAGE_SET:
      {
        struct ovectl_ratemanage_arg *ai=
          (struct ovectl_ratemanage_arg *)arg;
        if(ai==NULL){
          hi->managed=0;
        }else{
          hi->managed=ai->management_active;
          vorbis_encode_ctl(vi,OV_ECTL_RATEMANAGE_AVG,arg);
          vorbis_encode_ctl(vi,OV_ECTL_RATEMANAGE_HARD,arg);
        }
      }
      return 0;

    /* now deprecated *****************/
    case OV_ECTL_RATEMANAGE_AVG:
      {
        struct ovectl_ratemanage_arg *ai=
          (struct ovectl_ratemanage_arg *)arg;
        if(ai==NULL){
          hi->bitrate_av=0;
        }else{
          hi->bitrate_av=(ai->bitrate_av_lo+ai->bitrate_av_hi)*.5;
        }
      }
      return(0);
    /* now deprecated *****************/
    case OV_ECTL_RATEMANAGE_HARD:
      {
        struct ovectl_ratemanage_arg *ai=
          (struct ovectl_ratemanage_arg *)arg;
        if(ai==NULL){
          hi->bitrate_min=0;
          hi->bitrate_max=0;
        }else{
          hi->bitrate_min=ai->bitrate_hard_min;
          hi->bitrate_max=ai->bitrate_hard_max;
          hi->bitrate_reservoir=ai->bitrate_hard_window*
            (hi->bitrate_max+hi->bitrate_min)*.5;
        }
        if(hi->bitrate_reservoir<128.)
          hi->bitrate_reservoir=128.;
      }
      return(0);

      /* replacement ratemanage interface */
    case OV_ECTL_RATEMANAGE2_GET:
      {
        struct ovectl_ratemanage2_arg *ai=
          (struct ovectl_ratemanage2_arg *)arg;
        if(ai==NULL)return OV_EINVAL;

        ai->management_active=hi->managed;
        ai->bitrate_limit_min_kbps=hi->bitrate_min/1000;
        ai->bitrate_limit_max_kbps=hi->bitrate_max/1000;
        ai->bitrate_average_kbps=hi->bitrate_av/1000;
        ai->bitrate_average_damping=hi->bitrate_av_damp;
        ai->bitrate_limit_reservoir_bits=hi->bitrate_reservoir;
        ai->bitrate_limit_reservoir_bias=hi->bitrate_reservoir_bias;
      }
      return (0);
    case OV_ECTL_RATEMANAGE2_SET:
      {
        struct ovectl_ratemanage2_arg *ai=
          (struct ovectl_ratemanage2_arg *)arg;
        if(ai==NULL){
          hi->managed=0;
        }else{
          /* sanity check; only catch invariant violations */
          if(ai->bitrate_limit_min_kbps>0 &&
             ai->bitrate_average_kbps>0 &&
             ai->bitrate_limit_min_kbps>ai->bitrate_average_kbps)
            return OV_EINVAL;

          if(ai->bitrate_limit_max_kbps>0 &&
             ai->bitrate_average_kbps>0 &&
             ai->bitrate_limit_max_kbps<ai->bitrate_average_kbps)
            return OV_EINVAL;

          if(ai->bitrate_limit_min_kbps>0 &&
             ai->bitrate_limit_max_kbps>0 &&
             ai->bitrate_limit_min_kbps>ai->bitrate_limit_max_kbps)
            return OV_EINVAL;

          if(ai->bitrate_average_damping <= 0.)
            return OV_EINVAL;

          if(ai->bitrate_limit_reservoir_bits < 0)
            return OV_EINVAL;

          if(ai->bitrate_limit_reservoir_bias < 0.)
            return OV_EINVAL;

          if(ai->bitrate_limit_reservoir_bias > 1.)
            return OV_EINVAL;

          hi->managed=ai->management_active;
          hi->bitrate_min=ai->bitrate_limit_min_kbps * 1000;
          hi->bitrate_max=ai->bitrate_limit_max_kbps * 1000;
          hi->bitrate_av=ai->bitrate_average_kbps * 1000;
          hi->bitrate_av_damp=ai->bitrate_average_damping;
          hi->bitrate_reservoir=ai->bitrate_limit_reservoir_bits;
          hi->bitrate_reservoir_bias=ai->bitrate_limit_reservoir_bias;
        }
      }
      return 0;

    case OV_ECTL_LOWPASS_GET:
      {
        double *farg=(double *)arg;
        *farg=hi->lowpass_kHz;
      }
      return(0);
    case OV_ECTL_LOWPASS_SET:
      {
        double *farg=(double *)arg;
        hi->lowpass_kHz=*farg;

        if(hi->lowpass_kHz<2.)hi->lowpass_kHz=2.;
        if(hi->lowpass_kHz>99.)hi->lowpass_kHz=99.;
        hi->lowpass_altered=1;
      }
      return(0);
    case OV_ECTL_IBLOCK_GET:
      {
        double *farg=(double *)arg;
        *farg=hi->impulse_noisetune;
      }
      return(0);
    case OV_ECTL_IBLOCK_SET:
      {
        double *farg=(double *)arg;
        hi->impulse_noisetune=*farg;

        if(hi->impulse_noisetune>0.)hi->impulse_noisetune=0.;
        if(hi->impulse_noisetune<-15.)hi->impulse_noisetune=-15.;
      }
      return(0);
    case OV_ECTL_COUPLING_GET:
      {
        int *iarg=(int *)arg;
        *iarg=hi->coupling_p;
      }
      return(0);
    case OV_ECTL_COUPLING_SET:
      {
        const void *new_template;
        double new_base=0.;
        int *iarg=(int *)arg;
        hi->coupling_p=((*iarg)!=0);

        /* Fetching a new template can alter the base_setting, which
           many other parameters are based on.  Right now, the only
           parameter drawn from the base_setting that can be altered
           by an encctl is the lowpass, so that is explictly flagged
           to not be overwritten when we fetch a new template and
           recompute the dependant settings */
        new_template = get_setup_template(hi->coupling_p?vi->channels:-1,
                                          vi->rate,
                                          hi->req,
                                          hi->managed,
                                          &new_base);
        if(!hi->setup)return OV_EIMPL;
        hi->setup=new_template;
        hi->base_setting=new_base;
        vorbis_encode_setup_setting(vi,vi->channels,vi->rate);
      }
      return(0);
    }
    return(OV_EIMPL);
  }
  return(OV_EINVAL);
}