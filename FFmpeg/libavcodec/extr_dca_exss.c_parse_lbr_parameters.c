#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ lbr_size; } ;
struct TYPE_5__ {int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ DCAExssParser ;
typedef  TYPE_2__ DCAExssAsset ;

/* Variables and functions */
 scalar_t__ get_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void parse_lbr_parameters(DCAExssParser *s, DCAExssAsset *asset)
{
    // Size of LBR component in extension substream
    asset->lbr_size = get_bits(&s->gb, 14) + 1;

    // LBR sync word present flag
    if (get_bits1(&s->gb))
        // LBR sync distance
        skip_bits(&s->gb, 2);
}