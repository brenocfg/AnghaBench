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
typedef  int /*<<< orphan*/  zbar_scanner_t ;
struct TYPE_3__ {int /*<<< orphan*/ * scn; } ;
typedef  TYPE_1__ zbar_image_scanner_t ;

/* Variables and functions */
 int /*<<< orphan*/  zbar_scanner_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zbar_scanner_new_scan (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void quiet_border (zbar_image_scanner_t *iscn)
{
    /* flush scanner pipeline */
    zbar_scanner_t *scn = iscn->scn;
    zbar_scanner_flush(scn);
    zbar_scanner_flush(scn);
    zbar_scanner_new_scan(scn);
}