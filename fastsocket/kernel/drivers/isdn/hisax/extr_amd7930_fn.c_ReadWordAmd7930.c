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
struct IsdnCardState {int dummy; } ;
typedef  int WORD ;
typedef  int BYTE ;

/* Variables and functions */
 int rByteAMD (struct IsdnCardState*,int) ; 
 int /*<<< orphan*/  wByteAMD (struct IsdnCardState*,int,int) ; 

__attribute__((used)) static WORD /* macro rWordAMD */
ReadWordAmd7930(struct IsdnCardState *cs, BYTE reg)
{
        WORD res;
        /* direct access register */
        if(reg < 8) {
        	res = rByteAMD(cs, reg);
                res += 256*rByteAMD(cs, reg);
        }
        /* indirect access register */
        else {
                wByteAMD(cs, 0x00, reg);
	        res = rByteAMD(cs, 0x01);
                res += 256*rByteAMD(cs, 0x01);
        }
	return (res);
}