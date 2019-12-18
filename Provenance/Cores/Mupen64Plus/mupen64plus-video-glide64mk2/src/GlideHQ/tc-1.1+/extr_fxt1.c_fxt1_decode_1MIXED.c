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
typedef  int dword ;
typedef  int byte ;

/* Variables and functions */
 size_t ACOMP ; 
 size_t BCOMP ; 
 int CC_SEL (int const*,int) ; 
 size_t GCOMP ; 
 int LERP (int,int,int,int) ; 
 size_t RCOMP ; 
 int UP5 (int) ; 
 int UP6 (int,int) ; 
 int /*<<< orphan*/  ZERO_4UBV (int*) ; 

__attribute__((used)) static void
fxt1_decode_1MIXED (const byte *code, int t, byte *rgba)
{
    const dword *cc;
    int col[2][3];
    int glsb, selb;

    cc = (const dword *)code;
    if (t & 16) {
	t &= 15;
	t = (cc[1] >> (t * 2)) & 3;
	/* col 2 */
	col[0][BCOMP] = (*(const dword *)(code + 11)) >> 6;
	col[0][GCOMP] = CC_SEL(cc, 99);
	col[0][RCOMP] = CC_SEL(cc, 104);
	/* col 3 */
	col[1][BCOMP] = CC_SEL(cc, 109);
	col[1][GCOMP] = CC_SEL(cc, 114);
	col[1][RCOMP] = CC_SEL(cc, 119);
	glsb = CC_SEL(cc, 126);
	selb = CC_SEL(cc, 33);
    } else {
	t = (cc[0] >> (t * 2)) & 3;
	/* col 0 */
	col[0][BCOMP] = CC_SEL(cc, 64);
	col[0][GCOMP] = CC_SEL(cc, 69);
	col[0][RCOMP] = CC_SEL(cc, 74);
	/* col 1 */
	col[1][BCOMP] = CC_SEL(cc, 79);
	col[1][GCOMP] = CC_SEL(cc, 84);
	col[1][RCOMP] = CC_SEL(cc, 89);
	glsb = CC_SEL(cc, 125);
	selb = CC_SEL(cc, 1);
    }

    if (CC_SEL(cc, 124) & 1) {
	/* alpha[0] == 1 */

	if (t == 3) {
	    ZERO_4UBV(rgba);
	} else {
	    if (t == 0) {
		rgba[BCOMP] = UP5(col[0][BCOMP]);
		rgba[GCOMP] = UP5(col[0][GCOMP]);
		rgba[RCOMP] = UP5(col[0][RCOMP]);
	    } else if (t == 2) {
		rgba[BCOMP] = UP5(col[1][BCOMP]);
		rgba[GCOMP] = UP6(col[1][GCOMP], glsb);
		rgba[RCOMP] = UP5(col[1][RCOMP]);
	    } else {
		rgba[BCOMP] = (UP5(col[0][BCOMP]) + UP5(col[1][BCOMP])) / 2;
		rgba[GCOMP] = (UP5(col[0][GCOMP]) + UP6(col[1][GCOMP], glsb)) / 2;
		rgba[RCOMP] = (UP5(col[0][RCOMP]) + UP5(col[1][RCOMP])) / 2;
	    }
	    rgba[ACOMP] = 255;
	}
    } else {
	/* alpha[0] == 0 */

	if (t == 0) {
	    rgba[BCOMP] = UP5(col[0][BCOMP]);
	    rgba[GCOMP] = UP6(col[0][GCOMP], glsb ^ selb);
	    rgba[RCOMP] = UP5(col[0][RCOMP]);
	} else if (t == 3) {
	    rgba[BCOMP] = UP5(col[1][BCOMP]);
	    rgba[GCOMP] = UP6(col[1][GCOMP], glsb);
	    rgba[RCOMP] = UP5(col[1][RCOMP]);
	} else {
	    rgba[BCOMP] = LERP(3, t, UP5(col[0][BCOMP]), UP5(col[1][BCOMP]));
	    rgba[GCOMP] = LERP(3, t, UP6(col[0][GCOMP], glsb ^ selb),
				     UP6(col[1][GCOMP], glsb));
	    rgba[RCOMP] = LERP(3, t, UP5(col[0][RCOMP]), UP5(col[1][RCOMP]));
	}
	rgba[ACOMP] = 255;
    }
}