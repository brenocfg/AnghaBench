#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  bda; } ;
typedef  TYPE_1__ tGATTS_SRV_CHG ;
typedef  int /*<<< orphan*/  list_t ;
typedef  int /*<<< orphan*/  list_node_t ;
struct TYPE_5__ {int /*<<< orphan*/  srv_chg_clt_q; } ;
typedef  int /*<<< orphan*/ * BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*,...) ; 
 int /*<<< orphan*/ * fixed_queue_get_list (int /*<<< orphan*/ ) ; 
 scalar_t__ fixed_queue_is_empty (int /*<<< orphan*/ ) ; 
 TYPE_3__ gatt_cb ; 
 int /*<<< orphan*/ * list_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* list_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_next (int /*<<< orphan*/  const*) ; 
 scalar_t__ list_node (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tGATTS_SRV_CHG *gatt_is_bda_in_the_srv_chg_clt_list (BD_ADDR bda)
{
    tGATTS_SRV_CHG *p_buf = NULL;

    GATT_TRACE_DEBUG("gatt_is_bda_in_the_srv_chg_clt_list :%02x-%02x-%02x-%02x-%02x-%02x",
                     bda[0],  bda[1], bda[2],  bda[3], bda[4],  bda[5]);

    if (fixed_queue_is_empty(gatt_cb.srv_chg_clt_q)) {
        return NULL;
	}

    list_t *list = fixed_queue_get_list(gatt_cb.srv_chg_clt_q);
    for (const list_node_t *node = list_begin(list); node != list_end(list);
         node = list_next(node)) {
        p_buf = (tGATTS_SRV_CHG *)list_node(node);
        if (!memcmp( bda, p_buf->bda, BD_ADDR_LEN)) {
            GATT_TRACE_DEBUG("bda is in the srv chg clt list");
            break;
        }
    }

    return p_buf;
}