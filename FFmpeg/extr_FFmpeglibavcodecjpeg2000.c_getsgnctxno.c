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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int JPEG2000_T1_SGN_E ; 
 int JPEG2000_T1_SGN_N ; 
 int JPEG2000_T1_SGN_S ; 
 int JPEG2000_T1_SGN_W ; 
 int JPEG2000_T1_SIG_E ; 
 int JPEG2000_T1_SIG_N ; 
 int JPEG2000_T1_SIG_S ; 
 int JPEG2000_T1_SIG_W ; 
 int** contribtab ; 
 int** ctxlbltab ; 
 int /*<<< orphan*/ ** xorbittab ; 

__attribute__((used)) static int getsgnctxno(int flag, uint8_t *xorbit)
{
    int vcontrib, hcontrib;

    hcontrib = contribtab[flag & JPEG2000_T1_SIG_E ? flag & JPEG2000_T1_SGN_E ? 1 : 2 : 0]
                         [flag & JPEG2000_T1_SIG_W ? flag & JPEG2000_T1_SGN_W ? 1 : 2 : 0] + 1;
    vcontrib = contribtab[flag & JPEG2000_T1_SIG_S ? flag & JPEG2000_T1_SGN_S ? 1 : 2 : 0]
                         [flag & JPEG2000_T1_SIG_N ? flag & JPEG2000_T1_SGN_N ? 1 : 2 : 0] + 1;
    *xorbit = xorbittab[hcontrib][vcontrib];

    return ctxlbltab[hcontrib][vcontrib];
}