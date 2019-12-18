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
struct mgsl_struct {int dummy; } ;

/* Variables and functions */
 int BIT7 ; 
 int /*<<< orphan*/  CCSR ; 
 int usc_InReg (struct mgsl_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usc_loopmode_active( struct mgsl_struct * info)
{
 	return usc_InReg( info, CCSR ) & BIT7 ? 1 : 0 ;
}