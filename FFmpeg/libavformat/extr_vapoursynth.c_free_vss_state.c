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
typedef  int /*<<< orphan*/  uint8_t ;
struct VSState {scalar_t__ vss; } ;

/* Variables and functions */
 int /*<<< orphan*/  vsscript_finalize () ; 
 int /*<<< orphan*/  vsscript_freeScript (scalar_t__) ; 

__attribute__((used)) static void free_vss_state(void *opaque, uint8_t *data)
{
    struct VSState *vss = opaque;

    if (vss->vss) {
        vsscript_freeScript(vss->vss);
        vsscript_finalize();
    }
}