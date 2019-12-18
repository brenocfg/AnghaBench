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
struct TYPE_3__ {int mdivk; int c1_f0; int c3_f2; int c0_hf; int c2_hf; unsigned int c0divpos; int c1divpos; unsigned int c2divpos; int c3divpos; int c0sw4; int c1sw4; } ;
typedef  TYPE_1__ PokeyState ;

/* Variables and functions */

__attribute__((used)) static void Update_audctl(PokeyState* ps, unsigned char val)
{
    int nc0_hf,nc2_hf,nc1_f0,nc3_f2,nc0sw4,nc1sw4,new_divk;
    int recalc0=0;
    int recalc1=0;
    int recalc2=0;
    int recalc3=0;

    unsigned int cnt0 = 0;
    unsigned int cnt1 = 0;
    unsigned int cnt2 = 0;
    unsigned int cnt3 = 0;

    nc0_hf = (val & 0x40) != 0;
    nc2_hf = (val & 0x20) != 0;
    nc1_f0 = (val & 0x10) != 0;
    nc3_f2 = (val & 0x08) != 0;
    nc0sw4 = (val & 0x04) != 0;
    nc1sw4 = (val & 0x02) != 0;
    if(val & 0x01)
        new_divk = 114;
    else
        new_divk = 28;

    if(new_divk != ps->mdivk)
    {
        recalc0 = recalc1 = recalc2 = recalc3 = 1;
    }
    if(nc1_f0 != ps->c1_f0)
    {
        recalc0 = recalc1 = 1;
    }
    if(nc3_f2 != ps->c3_f2)
    {
        recalc2 = recalc3 = 1;
    }
    if(nc0_hf != ps->c0_hf)
    {
        recalc0 = 1;
        if(nc1_f0)
            recalc1 = 1;
    }
    if(nc2_hf != ps->c2_hf)
    {
        recalc2 = 1;
        if(nc3_f2)
            recalc3 = 1;
    }

    if(recalc0)
    {
        if(ps->c0_hf)
            cnt0 = ps->c0divpos;
        else
            cnt0 = ps->c0divpos/ps->mdivk;
    }
    if(recalc1)
    {
        if(ps->c1_f0)
        {
            if(ps->c0_hf)
                cnt1 = ps->c1divpos/256;
            else
                cnt1 = ps->c1divpos/256/ps->mdivk;
        }
        else
        {
            cnt1 = ps->c1divpos/ps->mdivk;
        }
    }
    if(recalc2)
    {
        if(ps->c2_hf)
            cnt2 = ps->c2divpos;
        else
            cnt2 = ps->c2divpos/ps->mdivk;
    }
    if(recalc3)
    {
        if(ps->c3_f2)
        {
            if(ps->c2_hf)
                cnt3 = ps->c3divpos/256;
            else
                cnt3 = ps->c3divpos/256/ps->mdivk;
        }
    }

    if(recalc0)
    {
        if(nc0_hf)
            ps->c0divpos = cnt0;
        else
            ps->c0divpos = cnt0*new_divk;
    }
    if(recalc1)
    {
        if(nc1_f0)
        {
            if(nc0_hf)
                ps->c1divpos = cnt1*256+cnt0;
            else
                ps->c1divpos = (cnt1*256+cnt0)*new_divk;
        }
        else
        {
            ps->c1divpos = cnt1*new_divk;
        }
    }

    if(recalc2)
    {
        if(nc2_hf)
            ps->c2divpos = cnt2;
        else
            ps->c2divpos = cnt2*new_divk;
    }
    if(recalc3)
    {
        if(nc3_f2)
        {
            if(nc2_hf)
                ps->c3divpos = cnt3*256+cnt2;
            else
                ps->c3divpos = (cnt3*256+cnt2)*new_divk;
        }
    }

    ps->c0_hf = nc0_hf;
    ps->c2_hf = nc2_hf;
    ps->c1_f0 = nc1_f0;
    ps->c3_f2 = nc3_f2;
    ps->c0sw4 = nc0sw4;
    ps->c1sw4 = nc1sw4;
    ps->mdivk = new_divk;
}