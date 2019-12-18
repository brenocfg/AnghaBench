#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int sec_flags; scalar_t__ hci_handle; scalar_t__ last_author_service_id; int /*<<< orphan*/  sec_state; scalar_t__ is_originator; int /*<<< orphan*/  sec_bd_name; int /*<<< orphan*/  dev_class; int /*<<< orphan*/  bd_addr; TYPE_1__* p_cur_service; } ;
typedef  TYPE_3__ tBTM_SEC_DEV_REC ;
typedef  scalar_t__ UINT8 ;
struct TYPE_8__ {scalar_t__ (* p_authorize_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__,scalar_t__) ;} ;
struct TYPE_10__ {TYPE_2__ api; } ;
struct TYPE_7__ {scalar_t__ service_id; scalar_t__* term_service_name; scalar_t__* orig_service_name; } ;

/* Variables and functions */
 scalar_t__ BTM_CMD_STARTED ; 
 scalar_t__ BTM_MODE_UNSUPPORTED ; 
 int BTM_SEC_AUTHORIZED ; 
 scalar_t__ BTM_SEC_INVALID_HANDLE ; 
 int BTM_SEC_NAME_KNOWN ; 
 scalar_t__ BTM_SEC_NO_LAST_SERVICE_ID ; 
 int /*<<< orphan*/  BTM_SEC_STATE_AUTHORIZING ; 
 int /*<<< orphan*/  BTM_SEC_STATE_IDLE ; 
 scalar_t__ BTM_SUCCESS ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,scalar_t__) ; 
 TYPE_6__ btm_cb ; 
 int /*<<< orphan*/  btm_sec_start_get_name (TYPE_3__*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static UINT8 btm_sec_start_authorization (tBTM_SEC_DEV_REC *p_dev_rec)
{
    UINT8    result;
    UINT8   *p_service_name = NULL;
    UINT8    service_id;

    if ((p_dev_rec->sec_flags & BTM_SEC_NAME_KNOWN)
            || (p_dev_rec->hci_handle == BTM_SEC_INVALID_HANDLE)) {
        if (!btm_cb.api.p_authorize_callback) {
            return (BTM_MODE_UNSUPPORTED);
        }

        if (p_dev_rec->p_cur_service) {
#if BTM_SEC_SERVICE_NAME_LEN > 0
            if (p_dev_rec->is_originator) {
                p_service_name = p_dev_rec->p_cur_service->orig_service_name;
            } else {
                p_service_name = p_dev_rec->p_cur_service->term_service_name;
            }
#endif
            service_id = p_dev_rec->p_cur_service->service_id;
        } else {
            service_id = 0;
        }

        /* Send authorization request if not already sent during this service connection */
        if (p_dev_rec->last_author_service_id == BTM_SEC_NO_LAST_SERVICE_ID
                || p_dev_rec->last_author_service_id != service_id) {
            p_dev_rec->sec_state = BTM_SEC_STATE_AUTHORIZING;
            result = (*btm_cb.api.p_authorize_callback) (p_dev_rec->bd_addr,
                     p_dev_rec->dev_class,
                     p_dev_rec->sec_bd_name,
                     p_service_name,
                     service_id,
                     p_dev_rec->is_originator);
        }

        else {  /* Already authorized once for this L2CAP bringup */
            BTM_TRACE_DEBUG ("btm_sec_start_authorization: (Ignoring extra Authorization prompt for service %d)\n", service_id);
            return (BTM_SUCCESS);
        }

        if (result == BTM_SUCCESS) {
            p_dev_rec->sec_flags |= BTM_SEC_AUTHORIZED;

            /* Save the currently authorized service in case we are asked again by another multiplexer layer */
            if (!p_dev_rec->is_originator) {
                p_dev_rec->last_author_service_id = service_id;
            }

            p_dev_rec->sec_state = BTM_SEC_STATE_IDLE;
        }
        return (result);
    }
    btm_sec_start_get_name (p_dev_rec);
    return (BTM_CMD_STARTED);
}