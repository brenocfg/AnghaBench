#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  void* qev_t ;
struct TYPE_18__ {size_t outvol_0; size_t outvol_1; size_t outvol_2; size_t outvol_3; size_t speaker; void* outvol_all; int c0divpos; int c1divpos; int c2divpos; int c3divpos; size_t poly5pos; size_t poly4pos; size_t poly9pos; size_t poly17pos; int c0divstart; int c1divstart; int c0divstart_p; int skctl; int c2divstart; int c3divstart; int c2divstart_p; size_t (* readout_0 ) (TYPE_1__*) ;size_t (* readout_1 ) (TYPE_1__*) ;size_t (* readout_2 ) (TYPE_1__*) ;size_t (* readout_3 ) (TYPE_1__*) ;scalar_t__ c1sw4; scalar_t__ c3_f2; int /*<<< orphan*/  (* event_3 ) (TYPE_1__*,int,int,int) ;int /*<<< orphan*/  c3stop; scalar_t__ c0sw4; int /*<<< orphan*/  (* event_2 ) (TYPE_1__*,int,int,int) ;int /*<<< orphan*/  c2stop; scalar_t__ c1_f0; int /*<<< orphan*/  (* event_1 ) (TYPE_1__*,int,int,int) ;int /*<<< orphan*/  c1stop; int /*<<< orphan*/  (* event_0 ) (TYPE_1__*,int,int,int) ;int /*<<< orphan*/  c0stop; scalar_t__ selpoly9; scalar_t__ forcero; } ;
typedef  TYPE_1__ PokeyState ;

/* Variables and functions */
 int /*<<< orphan*/  add_change (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  advance_polies (TYPE_1__*,int) ; 
 int /*<<< orphan*/  bump_qe_subticks (TYPE_1__*,int) ; 
 void** pokeymix ; 
 int* poly17tbl ; 
 int* poly4tbl ; 
 int* poly5tbl ; 
 int* poly9tbl ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int,int,int) ; 
 int stub10 (TYPE_1__*) ; 
 size_t stub11 (TYPE_1__*) ; 
 int stub12 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__*,int,int,int) ; 
 size_t stub5 (TYPE_1__*) ; 
 int stub6 (TYPE_1__*) ; 
 size_t stub7 (TYPE_1__*) ; 
 int stub8 (TYPE_1__*) ; 
 size_t stub9 (TYPE_1__*) ; 

__attribute__((used)) static void advance_ticks(PokeyState* ps, int ticks)
{
    int ta,tbe, tbe0, tbe1, tbe2, tbe3;
    int p5v,p4v,p917v;

    qev_t outvol_new;
    int need0=0;
    int need1=0;
    int need2=0;
    int need3=0;

    int need=0;

    if (ticks <= 0) return;
    if(ps->forcero)
    {
        ps->forcero = 0;
#ifdef NONLINEAR_MIXING
#ifdef SYNCHRONIZED_SOUND
        outvol_new = pokeymix[ps->outvol_0 + ps->outvol_1 + ps->outvol_2 + ps->outvol_3 + ps->speaker];
#else
        outvol_new = pokeymix[ps->outvol_0 + ps->outvol_1 + ps->outvol_2 + ps->outvol_3];
#endif /* SYNCHRONIZED_SOUND */
#else
        outvol_new = ps->outvol_0 + ps->outvol_1 + ps->outvol_2 + ps->outvol_3;
#ifdef SYNCHRONIZED_SOUND
        outvol_new += ps->speaker;
#endif /* SYNCHRONIZED_SOUND */
#endif /* NONLINEAR_MIXING */
        if(outvol_new != ps->outvol_all)
        {
            ps->outvol_all = outvol_new;
            add_change(ps, outvol_new);
        }
    }

    while(ticks>0)
    {
        tbe0 = ps->c0divpos;
        tbe1 = ps->c1divpos;
        tbe2 = ps->c2divpos;
        tbe3 = ps->c3divpos;

        tbe = ticks+1;

#ifdef NONLINEAR_MIXING
        if(tbe0 < tbe)
            tbe = tbe0;
        if(tbe1 < tbe)
            tbe = tbe1;
        if(tbe2 < tbe)
            tbe = tbe2;
        if(tbe3 < tbe)
            tbe = tbe3;
#else
        if(!ps->c0stop && tbe0 < tbe)
            tbe = tbe0;
        if(!ps->c1stop && tbe1 < tbe)
            tbe = tbe1;
        if(!ps->c2stop && tbe2 < tbe)
            tbe = tbe2;
        if(!ps->c3stop && tbe3 < tbe)
            tbe = tbe3;
#endif

        if(tbe>ticks)
            ta = ticks;
        else
        {
            ta = tbe;
            need = 1;
        }

        ticks -= ta;

#ifdef NONLINEAR_MIXING
        ps->c0divpos -= ta;
        ps->c1divpos -= ta;
        ps->c2divpos -= ta;
        ps->c3divpos -= ta;
#else
        if(!ps->c0stop) ps->c0divpos -= ta;
        if(!ps->c1stop) ps->c1divpos -= ta;
        if(!ps->c2stop) ps->c2divpos -= ta;
        if(!ps->c3stop) ps->c3divpos -= ta;
#endif

        advance_polies(ps,ta);
        bump_qe_subticks(ps,ta);

        if(need)
        {
            p5v = poly5tbl[ps->poly5pos] & 1;
            p4v = poly4tbl[ps->poly4pos] & 1;
            if(ps->selpoly9)
                p917v = poly9tbl[ps->poly9pos] & 1;
            else
                p917v = poly17tbl[ps->poly17pos] & 1;

#ifdef NONLINEAR_MIXING
            if(ta == tbe0)
#else
            if(!ps->c0stop && ta == tbe0)
#endif
            {
                ps->event_0(ps,p5v,p4v,p917v);
                ps->c0divpos = ps->c0divstart;
                need0 = 1;
            }
#ifdef NONLINEAR_MIXING
            if(ta == tbe1)
#else
            if(!ps->c1stop && ta == tbe1)
#endif
            {
                ps->event_1(ps,p5v,p4v,p917v);
                ps->c1divpos = ps->c1divstart;
                if(ps->c1_f0)
                    ps->c0divpos = ps->c0divstart_p;
                need1 = 1;
                /*two-tone filter*/
                /*use if send break is on and two-tone mode is on*/
                /*reset channel 1 if channel 2 changed*/
                if((ps->skctl & 0x88) == 0x88) {
                    ps->c0divpos = ps->c0divstart;
                    /* it doesn't change the output state */
                    /*need0 = 1;*/
                }
            }
#ifdef NONLINEAR_MIXING
            if(ta == tbe2)
#else
            if(!ps->c2stop && ta == tbe2)
#endif
            {
                ps->event_2(ps,p5v,p4v,p917v);
                ps->c2divpos = ps->c2divstart;
                need2 = 1;
                if(ps->c0sw4)
                    need0 = 1;
            }
#ifdef NONLINEAR_MIXING
            if(ta == tbe3)
#else
            if(!ps->c3stop && ta == tbe3)
#endif
            {
                ps->event_3(ps,p5v,p4v,p917v);
                ps->c3divpos = ps->c3divstart;
                if(ps->c3_f2)
                    ps->c2divpos = ps->c2divstart_p;
                need3 = 1;
                if(ps->c1sw4)
                    need1 = 1;
            }

            if(need0)
            {
#ifdef NONLINEAR_MIXING
                ps->outvol_0 = ps->readout_0(ps);
#else
                ps->outvol_0 = 2*ps->readout_0(ps);
#endif
            }
            if(need1)
            {
#ifdef NONLINEAR_MIXING
                ps->outvol_1 = ps->readout_1(ps);
#else
                ps->outvol_1 = 2*ps->readout_1(ps);
#endif
            }
            if(need2)
            {
#ifdef NONLINEAR_MIXING
                ps->outvol_2 = ps->readout_2(ps);
#else
                ps->outvol_2 = 2*ps->readout_2(ps);
#endif
            }
            if(need3)
            {
#ifdef NONLINEAR_MIXING
                ps->outvol_3 = ps->readout_3(ps);
#else
                ps->outvol_3 = 2*ps->readout_3(ps);
#endif
            }

#ifdef NONLINEAR_MIXING
#ifdef SYNCHRONIZED_SOUND
            outvol_new = pokeymix[ps->outvol_0 + ps->outvol_1 + ps->outvol_2 + ps->outvol_3 + ps->speaker];
#else
            outvol_new = pokeymix[ps->outvol_0 + ps->outvol_1 + ps->outvol_2 + ps->outvol_3];
#endif /* SYNCHRONIZED_SOUND */
#else
            outvol_new = ps->outvol_0 + ps->outvol_1 + ps->outvol_2 + ps->outvol_3;
#ifdef SYNCHRONIZED_SOUND
            outvol_new += ps->speaker;
#endif /* SYNCHRONIZED_SOUND */
#endif /* NONLINEAR_MIXING */
            if(outvol_new != ps->outvol_all)
            {
                ps->outvol_all = outvol_new;
                add_change(ps, outvol_new);
            }
        }
    }
}