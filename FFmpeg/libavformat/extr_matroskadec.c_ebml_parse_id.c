#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {scalar_t__ id; } ;
typedef  TYPE_1__ EbmlSyntax ;

/* Variables and functions */

__attribute__((used)) static EbmlSyntax *ebml_parse_id(EbmlSyntax *syntax, uint32_t id)
{
    int i;

    // Whoever touches this should be aware of the duplication
    // existing in matroska_cluster_parsing.
    for (i = 0; syntax[i].id; i++)
        if (id == syntax[i].id)
            break;

    return &syntax[i];
}