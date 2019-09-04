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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  FFFILE ;

/* Variables and functions */
 int DBL_MANT_DIG ; 
 int DBL_MAX ; 
 int DBL_MIN ; 
 int /*<<< orphan*/  ERANGE ; 
 long long LLONG_MIN ; 
 double copysign (double,int) ; 
 int /*<<< orphan*/  errno ; 
 double scalbn (double,long long) ; 
 long long scanexp (int /*<<< orphan*/ *,int) ; 
 int shgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shlim (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shunget (int /*<<< orphan*/ *) ; 

__attribute__((used)) static double hexfloat(FFFILE *f, int bits, int emin, int sign, int pok)
{
    uint32_t x = 0;
    double y = 0;
    double scale = 1;
    double bias = 0;
    int gottail = 0, gotrad = 0, gotdig = 0;
    long long rp = 0;
    long long dc = 0;
    long long e2 = 0;
    int d;
    int c;

    c = shgetc(f);

    /* Skip leading zeros */
    for (; c=='0'; c = shgetc(f))
        gotdig = 1;

    if (c=='.') {
        gotrad = 1;
        c = shgetc(f);
        /* Count zeros after the radix point before significand */
        for (rp=0; c=='0'; c = shgetc(f), rp--) gotdig = 1;
    }

    for (; c-'0'<10U || (c|32)-'a'<6U || c=='.'; c = shgetc(f)) {
        if (c=='.') {
            if (gotrad) break;
            rp = dc;
            gotrad = 1;
        } else {
            gotdig = 1;
            if (c > '9') d = (c|32)+10-'a';
            else d = c-'0';
            if (dc<8) {
                x = x*16 + d;
            } else if (dc < DBL_MANT_DIG/4+1) {
                y += d*(scale/=16);
            } else if (d && !gottail) {
                y += 0.5*scale;
                gottail = 1;
            }
            dc++;
        }
    }
    if (!gotdig) {
        shunget(f);
        if (pok) {
            shunget(f);
            if (gotrad) shunget(f);
        } else {
            shlim(f, 0);
        }
        return sign * 0.0;
    }
    if (!gotrad) rp = dc;
    while (dc<8) x *= 16, dc++;
    if ((c|32)=='p') {
        e2 = scanexp(f, pok);
        if (e2 == LLONG_MIN) {
            if (pok) {
                shunget(f);
            } else {
                shlim(f, 0);
                return 0;
            }
            e2 = 0;
        }
    } else {
        shunget(f);
    }
    e2 += 4*rp - 32;

    if (!x) return sign * 0.0;
    if (e2 > -emin) {
        errno = ERANGE;
        return sign * DBL_MAX * DBL_MAX;
    }
    if (e2 < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        return sign * DBL_MIN * DBL_MIN;
    }

    while (x < 0x80000000) {
        if (y>=0.5) {
            x += x + 1;
            y += y - 1;
        } else {
            x += x;
            y += y;
        }
        e2--;
    }

    if (bits > 32+e2-emin) {
        bits = 32+e2-emin;
        if (bits<0) bits=0;
    }

    if (bits < DBL_MANT_DIG)
        bias = copysign(scalbn(1, 32+DBL_MANT_DIG-bits-1), sign);

    if (bits<32 && y && !(x&1)) x++, y=0;

    y = bias + sign*(double)x + sign*y;
    y -= bias;

    if (!y) errno = ERANGE;

    return scalbn(y, e2);
}