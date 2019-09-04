#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int exp; double bin_val; double dec_val; } ;

/* Variables and functions */
 double ff_exp10 (double) ; 
 TYPE_1__* si_prefixes ; 
 double strtod (char const*,char**) ; 
 double strtoul (char const*,char**,int) ; 

double av_strtod(const char *numstr, char **tail)
{
    double d;
    char *next;
    if(numstr[0]=='0' && (numstr[1]|0x20)=='x') {
        d = strtoul(numstr, &next, 16);
    } else
        d = strtod(numstr, &next);
    /* if parsing succeeded, check for and interpret postfixes */
    if (next!=numstr) {
        if (next[0] == 'd' && next[1] == 'B') {
            /* treat dB as decibels instead of decibytes */
            d = ff_exp10(d / 20);
            next += 2;
        } else if (*next >= 'E' && *next <= 'z') {
            int e= si_prefixes[*next - 'E'].exp;
            if (e) {
                if (next[1] == 'i') {
                    d*= si_prefixes[*next - 'E'].bin_val;
                    next+=2;
                } else {
                    d*= si_prefixes[*next - 'E'].dec_val;
                    next++;
                }
            }
        }

        if (*next=='B') {
            d*=8;
            next++;
        }
    }
    /* if requested, fill in tail with the position after the last parsed
       character */
    if (tail)
        *tail = next;
    return d;
}