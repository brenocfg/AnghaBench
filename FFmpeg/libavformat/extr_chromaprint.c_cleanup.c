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
struct TYPE_3__ {scalar_t__ ctx; } ;
typedef  TYPE_1__ ChromaprintMuxContext ;

/* Variables and functions */
 int /*<<< orphan*/  chromaprint_free (scalar_t__) ; 
 int /*<<< orphan*/  ff_lock_avformat () ; 
 int /*<<< orphan*/  ff_unlock_avformat () ; 

__attribute__((used)) static void cleanup(ChromaprintMuxContext *cpr)
{
    if (cpr->ctx) {
        ff_lock_avformat();
        chromaprint_free(cpr->ctx);
        ff_unlock_avformat();
    }
}