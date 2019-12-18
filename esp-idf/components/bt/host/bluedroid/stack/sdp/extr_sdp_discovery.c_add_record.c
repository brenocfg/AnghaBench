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
struct TYPE_5__ {struct TYPE_5__* p_next_rec; int /*<<< orphan*/  remote_bd_addr; int /*<<< orphan*/ * p_first_attr; } ;
typedef  TYPE_1__ tSDP_DISC_REC ;
struct TYPE_6__ {int mem_free; TYPE_1__* p_first_rec; scalar_t__ p_free_mem; } ;
typedef  TYPE_2__ tSDP_DISCOVERY_DB ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tSDP_DISC_REC *add_record (tSDP_DISCOVERY_DB *p_db, BD_ADDR p_bda)
{
    tSDP_DISC_REC   *p_rec;

    /* See if there is enough space in the database */
    if (p_db->mem_free < sizeof (tSDP_DISC_REC)) {
        return (NULL);
    }

    p_rec = (tSDP_DISC_REC *) p_db->p_free_mem;
    p_db->p_free_mem += sizeof (tSDP_DISC_REC);
    p_db->mem_free   -= sizeof (tSDP_DISC_REC);

    p_rec->p_first_attr = NULL;
    p_rec->p_next_rec   = NULL;

    memcpy (p_rec->remote_bd_addr, p_bda, BD_ADDR_LEN);

    /* Add the record to the end of chain */
    if (!p_db->p_first_rec) {
        p_db->p_first_rec = p_rec;
    } else {
        tSDP_DISC_REC   *p_rec1 = p_db->p_first_rec;

        while (p_rec1->p_next_rec) {
            p_rec1 = p_rec1->p_next_rec;
        }

        p_rec1->p_next_rec = p_rec;
    }

    return (p_rec);
}