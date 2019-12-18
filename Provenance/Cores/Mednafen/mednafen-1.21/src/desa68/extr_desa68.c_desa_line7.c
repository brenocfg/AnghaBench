#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ s8 ;
struct TYPE_2__ {int w; scalar_t__ reg9; } ;

/* Variables and functions */
 TYPE_1__ d ; 
 int /*<<< orphan*/  desa_ascii (scalar_t__) ; 
 int /*<<< orphan*/  desa_dcw () ; 
 int /*<<< orphan*/  desa_signifiant (int) ; 
 int /*<<< orphan*/  desa_str (char*) ; 

__attribute__((used)) static void desa_line7(void)
{
  if(d.w&0400) {
    desa_dcw();
  } else {
    desa_str("MOVEQ #");
    desa_signifiant((int)(s8)d.w);
    desa_ascii(',D0'+d.reg9);
  }
}