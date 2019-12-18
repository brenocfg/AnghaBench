#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  link_key ;
typedef  int /*<<< orphan*/  btc_config_section_iter_t ;
typedef  int /*<<< orphan*/  bt_status_t ;
struct TYPE_6__ {int /*<<< orphan*/  address; } ;
typedef  TYPE_1__ bt_bdaddr_t ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_7__ {int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  LINK_KEY ;
typedef  TYPE_2__ DEV_CLASS ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DmAddDevice (int /*<<< orphan*/ ,TYPE_2__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BTC_STORAGE_DEV_CLASS_STR ; 
 int /*<<< orphan*/  BTC_STORAGE_LINK_KEY_STR ; 
 int /*<<< orphan*/  BTC_STORAGE_LINK_KEY_TYPE_STR ; 
 int /*<<< orphan*/  BTC_STORAGE_PIN_LENGTH_STR ; 
 int /*<<< orphan*/  BTC_TRACE_DEBUG (char*,char const*) ; 
 int /*<<< orphan*/  BTC_TRACE_ERROR (char*,char const*) ; 
 int /*<<< orphan*/  BT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ btc_config_get_bin (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 scalar_t__ btc_config_get_int (char const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  btc_config_lock () ; 
 int /*<<< orphan*/ * btc_config_section_begin () ; 
 int /*<<< orphan*/  const* btc_config_section_end () ; 
 char* btc_config_section_name (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * btc_config_section_next (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  btc_config_unlock () ; 
 int /*<<< orphan*/  string_is_bdaddr (char const*) ; 
 int /*<<< orphan*/  string_to_bdaddr (char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  uint2devclass (int /*<<< orphan*/ ,TYPE_2__) ; 

__attribute__((used)) static bt_status_t btc_in_fetch_bonded_devices(int add)
{
    BOOLEAN bt_linkkey_file_found = FALSE;

    btc_config_lock();
    for (const btc_config_section_iter_t *iter = btc_config_section_begin(); iter != btc_config_section_end(); iter = btc_config_section_next(iter)) {
        const char *name = btc_config_section_name(iter);
        if (!string_is_bdaddr(name)) {
            continue;
        }

        BTC_TRACE_DEBUG("Remote device:%s\n", name);
        LINK_KEY link_key;
        size_t size = sizeof(link_key);
        if (btc_config_get_bin(name, BTC_STORAGE_LINK_KEY_STR, link_key, &size)) {
            int linkkey_type;
            if (btc_config_get_int(name, BTC_STORAGE_LINK_KEY_TYPE_STR, &linkkey_type)) {
                bt_bdaddr_t bd_addr;
                string_to_bdaddr(name, &bd_addr);
                if (add) {
                    DEV_CLASS dev_class = {0, 0, 0};
                    int cod;
                    int pin_length = 0;
                    if (btc_config_get_int(name, BTC_STORAGE_DEV_CLASS_STR, &cod)) {
                        uint2devclass((UINT32)cod, dev_class);
                    }
                    btc_config_get_int(name, BTC_STORAGE_PIN_LENGTH_STR, &pin_length);
#if (SMP_INCLUDED == TRUE)
                    BTA_DmAddDevice(bd_addr.address, dev_class, link_key, 0, 0,
                                    (UINT8)linkkey_type, 0, pin_length);
#endif  ///SMP_INCLUDED == TRUE
                }
                bt_linkkey_file_found = TRUE;
            } else {
                BTC_TRACE_ERROR("bounded device:%s, LinkKeyType or PinLength is invalid\n", name);
            }
        }
        if (!bt_linkkey_file_found) {
            BTC_TRACE_DEBUG("Remote device:%s, no link key\n", name);
        }
    }
    btc_config_unlock();

    return BT_STATUS_SUCCESS;
}