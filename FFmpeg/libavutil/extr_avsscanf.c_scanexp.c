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
 int INT_MAX ; 
 int LLONG_MAX ; 
 long long LLONG_MIN ; 
 int shgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shunget (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long long scanexp(FFFILE *f, int pok)
{
    int c;
    int x;
    long long y;
    int neg = 0;

    c = shgetc(f);
    if (c=='+' || c=='-') {
        neg = (c=='-');
        c = shgetc(f);
        if (c-'0'>=10U && pok) shunget(f);
    }
    if (c-'0'>=10U) {
        shunget(f);
        return LLONG_MIN;
    }
    for (x=0; c-'0'<10U && x<INT_MAX/10; c = shgetc(f))
        x = 10*x + c-'0';
    for (y=x; c-'0'<10U && y<LLONG_MAX/100; c = shgetc(f))
        y = 10*y + c-'0';
    for (; c-'0'<10U; c = shgetc(f));
    shunget(f);
    return neg ? -y : y;
}