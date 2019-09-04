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
typedef  int /*<<< orphan*/  FFFILE ;

/* Variables and functions */
 int DBL_MANT_DIG ; 
 int /*<<< orphan*/  DBL_MIN_EXP ; 
 int /*<<< orphan*/  EINVAL ; 
 int FLT_MANT_DIG ; 
 int /*<<< orphan*/  FLT_MIN_EXP ; 
 int INFINITY ; 
 double NAN ; 
 scalar_t__ av_isspace (int) ; 
 double decfloat (int /*<<< orphan*/ *,int,int,int,int,int) ; 
 int /*<<< orphan*/  errno ; 
 double hexfloat (int /*<<< orphan*/ *,int,int,int,int) ; 
 char shgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shlim (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shunget (int /*<<< orphan*/ *) ; 

__attribute__((used)) static double fffloatscan(FFFILE *f, int prec, int pok)
{
    int sign = 1;
    size_t i;
    int bits;
    int emin;
    int c;

    switch (prec) {
    case 0:
        bits = FLT_MANT_DIG;
        emin = FLT_MIN_EXP-bits;
        break;
    case 1:
        bits = DBL_MANT_DIG;
        emin = DBL_MIN_EXP-bits;
        break;
    case 2:
        bits = DBL_MANT_DIG;
        emin = DBL_MIN_EXP-bits;
        break;
    default:
        return 0;
    }

    while (av_isspace((c = shgetc(f))));

    if (c=='+' || c=='-') {
        sign -= 2*(c=='-');
        c = shgetc(f);
    }

    for (i=0; i<8 && (c|32)=="infinity"[i]; i++)
        if (i<7) c = shgetc(f);
    if (i==3 || i==8 || (i>3 && pok)) {
        if (i!=8) {
            shunget(f);
            if (pok) for (; i>3; i--) shunget(f);
        }
        return sign * INFINITY;
    }
    if (!i) for (i=0; i<3 && (c|32)=="nan"[i]; i++)
        if (i<2) c = shgetc(f);
    if (i==3) {
        if (shgetc(f) != '(') {
            shunget(f);
            return NAN;
        }
        for (i=1; ; i++) {
            c = shgetc(f);
            if (c-'0'<10U || c-'A'<26U || c-'a'<26U || c=='_')
                continue;
            if (c==')') return NAN;
            shunget(f);
            if (!pok) {
                errno = EINVAL;
                shlim(f, 0);
                return 0;
            }
            while (i--) shunget(f);
            return NAN;
        }
        return NAN;
    }

    if (i) {
        shunget(f);
        errno = EINVAL;
        shlim(f, 0);
        return 0;
    }

    if (c=='0') {
        c = shgetc(f);
        if ((c|32) == 'x')
            return hexfloat(f, bits, emin, sign, pok);
        shunget(f);
        c = '0';
    }

    return decfloat(f, c, bits, emin, sign, pok);
}