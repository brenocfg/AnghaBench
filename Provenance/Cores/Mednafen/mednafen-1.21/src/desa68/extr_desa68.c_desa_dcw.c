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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {scalar_t__ status; scalar_t__ w; } ;

/* Variables and functions */
 TYPE_1__ d ; 
 int /*<<< orphan*/  desa_char (char) ; 
 int /*<<< orphan*/  desa_str (char*) ; 
 int /*<<< orphan*/  desa_uhexacat (int /*<<< orphan*/ ,int,char) ; 

__attribute__((used)) static void desa_dcw(void)
{
  desa_str("DC.W");
  desa_char (' ');
  desa_uhexacat((u16)d.w, 4, '$');
  d.status = 0;
}