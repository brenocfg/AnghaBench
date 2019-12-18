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
typedef  int __u8 ;

/* Variables and functions */
#define  BOF 130 
#define  CE 129 
#define  EOF 128 
 int IRDA_TRANS ; 

__attribute__((used)) static inline int stuff_byte(__u8 byte, __u8 *buf)
{
	switch (byte) {
	case BOF: /* FALLTHROUGH */
	case EOF: /* FALLTHROUGH */
	case CE:
		/* Insert transparently coded */
		buf[0] = CE;               /* Send link escape */
		buf[1] = byte^IRDA_TRANS;    /* Complement bit 5 */
		return 2;
		/* break; */
	default:
		 /* Non-special value, no transparency required */
		buf[0] = byte;
		return 1;
		/* break; */
	}
}