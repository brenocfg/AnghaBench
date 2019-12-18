#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int format; int /*<<< orphan*/  short_name; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__ item; } ;

/* Variables and functions */
 int HB_MUX_INVALID ; 
 TYPE_2__* hb_containers ; 
 int hb_containers_count ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char const*) ; 

int hb_container_get_from_name(const char *name)
{
    if (name == NULL || *name == '\0')
        goto fail;

    int i;
    for (i = 0; i < hb_containers_count; i++)
    {
        if (!strcasecmp(hb_containers[i].item.name,       name) ||
            !strcasecmp(hb_containers[i].item.short_name, name))
        {
            return hb_containers[i].item.format;
        }
    }

fail:
    return HB_MUX_INVALID;
}