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
typedef  int /*<<< orphan*/  u16 ;
struct wps_sm {int /*<<< orphan*/  eapol_version; } ;
struct l2_ethhdr {int dummy; } ;
struct ieee802_1x_hdr {int /*<<< orphan*/  length; int /*<<< orphan*/  type; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int /*<<< orphan*/  host_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct ieee802_1x_hdr*,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ieee802_1x_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* os_malloc (size_t) ; 

u8 *wps_sm_alloc_eapol(struct wps_sm *sm, u8 type,
                       const void *data, u16 data_len,
                       size_t *msg_len, void **data_pos)
{
    void *buffer;
    struct ieee802_1x_hdr *hdr;

    *msg_len = sizeof(struct ieee802_1x_hdr) + data_len;
    /* XXX: reserve l2_ethhdr is enough */
    buffer = os_malloc(*msg_len + sizeof(struct l2_ethhdr));

    if (buffer == NULL) {
        return NULL;
    }
    hdr = (struct ieee802_1x_hdr *)((char *)buffer + sizeof(struct l2_ethhdr));

    hdr->version = sm->eapol_version;
    hdr->type = type;
    hdr->length = host_to_be16(data_len);

    if (data) {
        memcpy(hdr + 1, data, data_len);
    } else {
        memset(hdr + 1, 0, data_len);
    }

    if (data_pos) {
        *data_pos = hdr + 1;
    }

    return (u8 *) hdr;
}