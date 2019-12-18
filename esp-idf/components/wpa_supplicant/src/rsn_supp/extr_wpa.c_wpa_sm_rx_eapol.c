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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct wpa_sm {scalar_t__ pairwise_cipher; scalar_t__ group_cipher; scalar_t__ proto; int /*<<< orphan*/  rx_replay_counter; scalar_t__ rx_replay_counter_set; } ;
struct wpa_eapol_key {int /*<<< orphan*/  key_data_length; int /*<<< orphan*/  replay_counter; int /*<<< orphan*/  key_info; int /*<<< orphan*/  type; } ;
struct ieee802_1x_hdr {int /*<<< orphan*/  type; int /*<<< orphan*/  version; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAPOL_KEY_TYPE_RSN ; 
 int /*<<< orphan*/  EAPOL_KEY_TYPE_WPA ; 
 int /*<<< orphan*/  EAPOL_VERSION ; 
 int /*<<< orphan*/  IEEE802_1X_TYPE_EAPOL_KEY ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 scalar_t__ WPA_CIPHER_CCMP ; 
 int WPA_GET_BE16 (int /*<<< orphan*/ ) ; 
 int WPA_KEY_INFO_ACK ; 
 int WPA_KEY_INFO_ENCR_KEY_DATA ; 
 int WPA_KEY_INFO_KEY_INDEX_MASK ; 
 int WPA_KEY_INFO_KEY_TYPE ; 
 int WPA_KEY_INFO_MIC ; 
 int WPA_KEY_INFO_REQUEST ; 
 int WPA_KEY_INFO_SMK_MESSAGE ; 
 int WPA_KEY_INFO_TYPE_HMAC_MD5_RC4 ; 
 int WPA_KEY_INFO_TYPE_HMAC_SHA1_AES ; 
 int WPA_KEY_INFO_TYPE_MASK ; 
 scalar_t__ WPA_PROTO_RSN ; 
 int /*<<< orphan*/  WPA_REPLAY_COUNTER_LEN ; 
 int be_to_host16 (int /*<<< orphan*/ ) ; 
 struct wpa_sm gWpaSm ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_eapol_key_dump (int /*<<< orphan*/ ,struct wpa_eapol_key*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ wpa_supplicant_decrypt_key_data (struct wpa_sm*,struct wpa_eapol_key*,int) ; 
 int /*<<< orphan*/  wpa_supplicant_process_1_of_2 (struct wpa_sm*,int /*<<< orphan*/ *,struct wpa_eapol_key*,int,int) ; 
 int /*<<< orphan*/  wpa_supplicant_process_1_of_4 (struct wpa_sm*,int /*<<< orphan*/ *,struct wpa_eapol_key*,int) ; 
 int /*<<< orphan*/  wpa_supplicant_process_3_of_4 (struct wpa_sm*,struct wpa_eapol_key*,int) ; 
 scalar_t__ wpa_supplicant_verify_eapol_key_mic (struct wpa_sm*,struct wpa_eapol_key*,int,int /*<<< orphan*/ *,int) ; 

int   wpa_sm_rx_eapol(u8 *src_addr, u8 *buf, u32 len)
{
    struct wpa_sm *sm = &gWpaSm;
    u32 plen, data_len, extra_len;
    struct ieee802_1x_hdr *hdr;
    struct wpa_eapol_key *key;
    u16 key_info, ver;
    u8 *tmp;
    int ret = -1;

    if (len < sizeof(*hdr) + sizeof(*key)) {       
#ifdef DEBUG_PRINT    
        wpa_printf(MSG_DEBUG, "WPA: EAPOL frame too short to be a WPA "
               "EAPOL-Key (len %lu, expecting at least %lu)",
               (unsigned long) len,
               (unsigned long) sizeof(*hdr) + sizeof(*key));
#endif
        return 0;
    }
    
       tmp = buf;
    
    hdr = (struct ieee802_1x_hdr *) tmp;
    key = (struct wpa_eapol_key *) (hdr + 1);
    plen = be_to_host16(hdr->length);
    data_len = plen + sizeof(*hdr);

#ifdef DEBUG_PRINT    
    wpa_printf(MSG_DEBUG, "IEEE 802.1X RX: version=%d type=%d length=%d\n",
           hdr->version, hdr->type, plen);
#endif
    
    if (hdr->version < EAPOL_VERSION) {
        /* TODO: backwards compatibility */
    }
    if (hdr->type != IEEE802_1X_TYPE_EAPOL_KEY) {
#ifdef DEBUG_PRINT    
        wpa_printf(MSG_DEBUG, "WPA: EAPOL frame (type %u) discarded, "
            "not a Key frame", hdr->type);
#endif
        ret = 0;
        goto out;
    }
    if (plen > len - sizeof(*hdr) || plen < sizeof(*key)) {
#ifdef DEBUG_PRINT        
        wpa_printf(MSG_DEBUG, "WPA: EAPOL frame payload size %lu "
               "invalid (frame size %lu)",
               (unsigned long) plen, (unsigned long) len);
#endif    
        ret = 0;
        goto out;
    }

    if (key->type != EAPOL_KEY_TYPE_WPA && key->type != EAPOL_KEY_TYPE_RSN)
    {
#ifdef DEBUG_PRINT    
        wpa_printf(MSG_DEBUG, "WPA: EAPOL-Key type (%d) unknown, "
               "discarded", key->type);
#endif
        ret = 0;
        goto out;
    }

    wpa_eapol_key_dump(MSG_MSGDUMP, key);

    wpa_hexdump(MSG_MSGDUMP, "WPA: RX EAPOL-Key", tmp, len);
    
    if (data_len < len) {
#ifdef DEBUG_PRINT    
        wpa_printf(MSG_DEBUG, "WPA: ignoring %lu bytes after the IEEE "
               "802.1X data\n", (unsigned long) len - data_len);
#endif    
    }
    key_info = WPA_GET_BE16(key->key_info);
    ver = key_info & WPA_KEY_INFO_TYPE_MASK;
    if (ver != WPA_KEY_INFO_TYPE_HMAC_MD5_RC4 &&
        ver != WPA_KEY_INFO_TYPE_HMAC_SHA1_AES) {
#ifdef DEBUG_PRINT    
        wpa_printf(MSG_DEBUG, "WPA: Unsupported EAPOL-Key descriptor "
               "version %d.", ver);
#endif        
        goto out;
    }

    if (sm->pairwise_cipher == WPA_CIPHER_CCMP &&
        ver != WPA_KEY_INFO_TYPE_HMAC_SHA1_AES) {
#ifdef DEBUG_PRINT    
           wpa_printf(MSG_DEBUG, "WPA: CCMP is used, but EAPOL-Key "
               "descriptor version (%d) is not 2.", ver);
#endif    
        if (sm->group_cipher != WPA_CIPHER_CCMP &&
            !(key_info & WPA_KEY_INFO_KEY_TYPE)) {
            /* Earlier versions of IEEE 802.11i did not explicitly
             * require version 2 descriptor for all EAPOL-Key
             * packets, so allow group keys to use version 1 if
             * CCMP is not used for them. */
            #ifdef DEBUG_PRINT         
              wpa_printf(MSG_DEBUG, "WPA: Backwards compatibility: "
                   "allow invalid version for non-CCMP group "
                   "keys");
            #endif    
        } else
            goto out;
    }


    if ( sm->rx_replay_counter_set &&
    	memcmp(key->replay_counter, sm->rx_replay_counter,
              WPA_REPLAY_COUNTER_LEN) <= 0) {
        #ifdef DEBUG_PRINT              
        wpa_printf(MSG_DEBUG, "WPA: EAPOL-Key Replay Counter did not"
               " increase - dropping packet");
        #endif    
        goto out;
    }

    if (!(key_info & (WPA_KEY_INFO_ACK | WPA_KEY_INFO_SMK_MESSAGE))) {
        #ifdef DEBUG_PRINT    
        wpa_printf(MSG_DEBUG, "WPA: No Ack bit in key_info");
         #endif    
        goto out;
    }

    if (key_info & WPA_KEY_INFO_REQUEST) {
        #ifdef DEBUG_PRINT        
        wpa_printf(MSG_DEBUG, "WPA: EAPOL-Key with Request bit - dropped");
        #endif    
        goto out;
    }

    if ((key_info & WPA_KEY_INFO_MIC) && 
        wpa_supplicant_verify_eapol_key_mic(sm, key, ver, tmp, data_len)) 
        goto out;
    
    extra_len = data_len - sizeof(*hdr) - sizeof(*key);

    if (WPA_GET_BE16(key->key_data_length) > extra_len) {
            #ifdef DEBUG_PRINT        
        wpa_printf(MSG_DEBUG, "WPA: Invalid EAPOL-Key "
            "frame - key_data overflow (%d > %lu)",
            WPA_GET_BE16(key->key_data_length),
            (unsigned long) extra_len);
        #endif        
        goto out;
    }
    extra_len = WPA_GET_BE16(key->key_data_length);

    if (sm->proto == WPA_PROTO_RSN &&
        (key_info & WPA_KEY_INFO_ENCR_KEY_DATA)) {
        if (wpa_supplicant_decrypt_key_data(sm, key, ver))
            goto out;
        extra_len = WPA_GET_BE16(key->key_data_length);
    }

    if (key_info & WPA_KEY_INFO_KEY_TYPE) {
        if (key_info & WPA_KEY_INFO_KEY_INDEX_MASK) {
             #ifdef DEBUG_PRINT    
            wpa_printf(MSG_DEBUG, "WPA: Ignored EAPOL-Key "
                   "(Pairwise) with non-zero key index");
          #endif  
            goto out;
        }

        if (key_info & WPA_KEY_INFO_MIC) {
            /* 3/4 4-Way Handshake */
            wpa_supplicant_process_3_of_4(sm, key, ver);
        } else {
            /* 1/4 4-Way Handshake */
            wpa_supplicant_process_1_of_4(sm, src_addr, key,
                              ver);
        }
    } else {
        if (key_info & WPA_KEY_INFO_MIC) {
            /* 1/2 Group Key Handshake */
            wpa_supplicant_process_1_of_2(sm, src_addr, key,
                              extra_len, ver);
        } else {
         #ifdef DEBUG_PRINT    
            wpa_printf(MSG_DEBUG, "WPA: EAPOL-Key (Group) "
                   "without Mic bit - dropped");
         #endif    
        }
    }

    ret = 1;

out:

    return ret;
}