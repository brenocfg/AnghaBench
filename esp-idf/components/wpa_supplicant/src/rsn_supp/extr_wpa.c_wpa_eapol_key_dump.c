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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct wpa_eapol_key {int /*<<< orphan*/  key_data_length; int /*<<< orphan*/  key_length; int /*<<< orphan*/  type; int /*<<< orphan*/  key_info; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int MSG_MSGDUMP ; 
 int WPA_GET_BE16 (int /*<<< orphan*/ ) ; 
 int WPA_KEY_INFO_ACK ; 
 int WPA_KEY_INFO_ENCR_KEY_DATA ; 
 int WPA_KEY_INFO_ERROR ; 
 int WPA_KEY_INFO_INSTALL ; 
 int WPA_KEY_INFO_KEY_INDEX_MASK ; 
 int WPA_KEY_INFO_KEY_INDEX_SHIFT ; 
 int WPA_KEY_INFO_KEY_TYPE ; 
 int WPA_KEY_INFO_MIC ; 
 int WPA_KEY_INFO_REQUEST ; 
 int WPA_KEY_INFO_SECURE ; 
 int WPA_KEY_INFO_TYPE_MASK ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,...) ; 

void   wpa_eapol_key_dump(int level, const struct wpa_eapol_key *key)
{
#ifdef DEBUG_PRINT
    if (level < MSG_MSGDUMP)
        return;

    u16 key_info = WPA_GET_BE16(key->key_info);

    wpa_printf(MSG_DEBUG, "  EAPOL-Key type=%d\n", key->type);
    wpa_printf(MSG_DEBUG, "  key_info 0x%x (ver=%d keyidx=%d rsvd=%d %s"
           "%s%s%s%s%s%s%s)\n",
           key_info, (u32)(key_info & WPA_KEY_INFO_TYPE_MASK),
           (u32)((key_info & WPA_KEY_INFO_KEY_INDEX_MASK) >>
           WPA_KEY_INFO_KEY_INDEX_SHIFT),
           (u32)((key_info & (BIT(13) | BIT(14) | BIT(15))) >> 13),
           key_info & WPA_KEY_INFO_KEY_TYPE ? "Pairwise" : "Group",
           key_info & WPA_KEY_INFO_INSTALL ? " Install" : "",
           key_info & WPA_KEY_INFO_ACK ? " Ack" : "",
           key_info & WPA_KEY_INFO_MIC ? " MIC" : "",
           key_info & WPA_KEY_INFO_SECURE ? " Secure" : "",
           key_info & WPA_KEY_INFO_ERROR ? " Error" : "",
           key_info & WPA_KEY_INFO_REQUEST ? " Request" : "",
           key_info & WPA_KEY_INFO_ENCR_KEY_DATA ? " Encr" : "");
    wpa_printf(MSG_DEBUG, "  key_length=%u key_data_length=%u\n",
           WPA_GET_BE16(key->key_length),
           WPA_GET_BE16(key->key_data_length));
#endif    
}