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
typedef  unsigned short u16 ;
struct r8a66597 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFIFOSEL ; 
 unsigned short CURPIPE ; 
 unsigned short mbw_value (struct r8a66597*) ; 
 int /*<<< orphan*/  r8a66597_mdfy (struct r8a66597*,unsigned short,unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8a66597_reg_wait (struct r8a66597*,int /*<<< orphan*/ ,unsigned short,unsigned short) ; 

__attribute__((used)) static inline void cfifo_change(struct r8a66597 *r8a66597, u16 pipenum)
{
	unsigned short mbw = mbw_value(r8a66597);

	r8a66597_mdfy(r8a66597, mbw | pipenum, mbw | CURPIPE, CFIFOSEL);
	r8a66597_reg_wait(r8a66597, CFIFOSEL, CURPIPE, pipenum);
}