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
struct TYPE_3__ {int /*<<< orphan*/  list_file; } ;
typedef  TYPE_1__ hb_batch_t ;

/* Variables and functions */
 int hb_list_count (int /*<<< orphan*/ ) ; 

int hb_batch_title_count( hb_batch_t * d )
{
    return hb_list_count( d->list_file );
}