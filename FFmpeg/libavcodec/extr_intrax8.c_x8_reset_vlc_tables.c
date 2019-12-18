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
struct TYPE_3__ {int /*<<< orphan*/ * j_orient_vlc; int /*<<< orphan*/  j_ac_vlc; int /*<<< orphan*/  j_dc_vlc; } ;
typedef  TYPE_1__ IntraX8Context ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void x8_reset_vlc_tables(IntraX8Context *w)
{
    memset(w->j_dc_vlc, 0, sizeof(w->j_dc_vlc));
    memset(w->j_ac_vlc, 0, sizeof(w->j_ac_vlc));
    w->j_orient_vlc = NULL;
}