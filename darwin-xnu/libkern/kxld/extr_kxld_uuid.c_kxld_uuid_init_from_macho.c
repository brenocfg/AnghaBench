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
struct uuid_command {int /*<<< orphan*/  has_uuid; int /*<<< orphan*/  uuid; } ;
typedef  struct uuid_command KXLDuuid ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  check (struct uuid_command*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
kxld_uuid_init_from_macho(KXLDuuid *uuid, struct uuid_command *src)
{
    check(uuid);
    check(src);

    memcpy(uuid->uuid, src->uuid, sizeof(uuid->uuid));
    uuid->has_uuid = TRUE;
}