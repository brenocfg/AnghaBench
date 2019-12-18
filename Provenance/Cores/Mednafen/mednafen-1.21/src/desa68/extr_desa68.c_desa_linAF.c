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
struct TYPE_2__ {int line; int /*<<< orphan*/  w; } ;

/* Variables and functions */
 TYPE_1__ d ; 
 int /*<<< orphan*/  desa_ascii (char) ; 
 int /*<<< orphan*/  desa_uhexacat (int /*<<< orphan*/ ,int,char) ; 

__attribute__((used)) static void desa_linAF(void)
{
  desa_ascii('LINE');
  desa_ascii('A '+((d.line-0xA)<<8));
  desa_uhexacat(d.w, 3, '$');
}