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
struct rtl_ieee80211_hdr {int /*<<< orphan*/  frame_ctl; } ;
struct ieee80211_hdr_4addr {int /*<<< orphan*/ * payload; } ;
struct ieee80211_hdr_3addr {int /*<<< orphan*/ * payload; } ;
struct ieee80211_hdr_2addr {int /*<<< orphan*/ * payload; } ;
struct ieee80211_hdr_1addr {int /*<<< orphan*/ * payload; } ;

/* Variables and functions */
#define  IEEE80211_1ADDR_LEN 131 
#define  IEEE80211_2ADDR_LEN 130 
#define  IEEE80211_3ADDR_LEN 129 
#define  IEEE80211_4ADDR_LEN 128 
 int ieee80211_get_hdrlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u8 *ieee80211_get_payload(struct rtl_ieee80211_hdr *hdr)
{
        switch (ieee80211_get_hdrlen(le16_to_cpu(hdr->frame_ctl))) {
        case IEEE80211_1ADDR_LEN:
                return ((struct ieee80211_hdr_1addr *)hdr)->payload;
        case IEEE80211_2ADDR_LEN:
                return ((struct ieee80211_hdr_2addr *)hdr)->payload;
        case IEEE80211_3ADDR_LEN:
                return ((struct ieee80211_hdr_3addr *)hdr)->payload;
        case IEEE80211_4ADDR_LEN:
                return ((struct ieee80211_hdr_4addr *)hdr)->payload;
        }
        return NULL;
}