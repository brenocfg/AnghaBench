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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  EL_ANOMALY ; 
 int /*<<< orphan*/  PicoWriteM68k8_ramc (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SekPcS68k ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void PicoWriteM68k16_ramc(u32 a, u32 d)
{
  elprintf(EL_ANOMALY, "ramcart w16: [%06x] %04x @%06x",
    a, d, SekPcS68k);
  PicoWriteM68k8_ramc(a + 1, d);
}