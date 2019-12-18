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
struct TYPE_3__ {int mode; } ;
typedef  TYPE_1__ PIA ;

/* Variables and functions */
 int /*<<< orphan*/  P1 ; 
 int /*<<< orphan*/  pi_swab16 (char*,int) ; 
 int /*<<< orphan*/  pi_swab32 (char*,int) ; 
 int /*<<< orphan*/  r1 () ; 
 int /*<<< orphan*/  w0 (char) ; 
 int /*<<< orphan*/  w2 (int) ; 
 int /*<<< orphan*/  w3 (int) ; 
 int /*<<< orphan*/  w4 (char) ; 
 int /*<<< orphan*/  w4l (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w4w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void comm_write_block( PIA *pi, char * buf, int count )

{       int	k;

        switch (pi->mode) {

        case 0:
        case 1: w0(0x68); P1;
        	for (k=0;k<count;k++) {
                        w2(5); w0(buf[k^1]); w2(7);
                }
                w2(5); w2(4);
                break;

        case 2: w3(0x48); (void)r1();
                for (k=0;k<count;k++) w4(buf[k^1]);
                break;

        case 3: w3(0x48); (void)r1();
                for (k=0;k<count/2;k++) w4w(pi_swab16(buf,k));
                break;

        case 4: w3(0x48); (void)r1();
                for (k=0;k<count/4;k++) w4l(pi_swab32(buf,k));
                break;


        }
}