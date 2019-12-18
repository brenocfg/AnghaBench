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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/ * uu; } ;
typedef  TYPE_1__ bt_uuid_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int,int,int,int) ; 

void uuid_to_string_legacy(bt_uuid_t *p_uuid, char *str)
{
    uint32_t uuid0, uuid4;
    uint16_t uuid1, uuid2, uuid3, uuid5;

    memcpy(&uuid0, &(p_uuid->uu[0]), 4);
    memcpy(&uuid1, &(p_uuid->uu[4]), 2);
    memcpy(&uuid2, &(p_uuid->uu[6]), 2);
    memcpy(&uuid3, &(p_uuid->uu[8]), 2);
    memcpy(&uuid4, &(p_uuid->uu[10]), 4);
    memcpy(&uuid5, &(p_uuid->uu[14]), 2);

    sprintf((char *)str, "%.8x-%.4x-%.4x-%.4x-%.8x%.4x",
            ntohl(uuid0), ntohs(uuid1),
            ntohs(uuid2), ntohs(uuid3),
            ntohl(uuid4), ntohs(uuid5));
    return;
}