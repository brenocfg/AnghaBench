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
struct r8a66597 {int dummy; } ;

/* Variables and functions */
 int BEMPE ; 
 int BRDYE ; 
 int CTRE ; 
 int DPRPU ; 
 int /*<<< orphan*/  INTENB0 ; 
 int /*<<< orphan*/  SYSCFG0 ; 
 int /*<<< orphan*/  r8a66597_bset (struct r8a66597*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r8a66597_usb_connect(struct r8a66597 *r8a66597)
{
	r8a66597_bset(r8a66597, CTRE, INTENB0);
	r8a66597_bset(r8a66597, BEMPE | BRDYE, INTENB0);

	r8a66597_bset(r8a66597, DPRPU, SYSCFG0);
}