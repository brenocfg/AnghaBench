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
typedef  int u8 ;

/* Variables and functions */
 int decodeFVteln (char*,unsigned long*,int*) ; 

__attribute__((used)) static int FVteln2capi20(char *teln, u8 AdditionalInfo[1+2+2+31])
{
	unsigned long bmask;
	int active;
	int rc, i;
   
	rc = decodeFVteln(teln, &bmask, &active);
	if (rc) return rc;
	/* Length */
	AdditionalInfo[0] = 2+2+31;
        /* Channel: 3 => use channel allocation */
        AdditionalInfo[1] = 3; AdditionalInfo[2] = 0;
	/* Operation: 0 => DTE mode, 1 => DCE mode */
        if (active) {
   		AdditionalInfo[3] = 0; AdditionalInfo[4] = 0;
   	} else {
   		AdditionalInfo[3] = 1; AdditionalInfo[4] = 0;
	}
	/* Channel mask array */
	AdditionalInfo[5] = 0; /* no D-Channel */
	for (i=1; i <= 30; i++)
		AdditionalInfo[5+i] = (bmask & (1 << i)) ? 0xff : 0;
	return 0;
}