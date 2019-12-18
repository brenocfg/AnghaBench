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
struct wpa_group {int /*<<< orphan*/ * Counter; int /*<<< orphan*/ * GMK; } ;
struct wpa_authenticator {struct wpa_group** addr; } ;
typedef  int /*<<< orphan*/  rkey ;
typedef  int /*<<< orphan*/  group ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int WPA_GMK_LEN ; 
 int WPA_NONCE_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct wpa_group**,int) ; 
 scalar_t__ os_get_random (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sha1_prf (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_get_ntp_timestamp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int wpa_group_init_gmk_and_counter(struct wpa_authenticator *wpa_auth,
                      struct wpa_group *group)
{
    u8 buf[ETH_ALEN + 8 + sizeof(group)];
    u8 rkey[32];

    if (os_get_random(group->GMK, WPA_GMK_LEN) < 0)
        return -1;
    wpa_hexdump_key(MSG_DEBUG, "GMK", group->GMK, WPA_GMK_LEN);

    /*
     * Counter = PRF-256(Random number, "Init Counter",
     *                   Local MAC Address || Time)
     */
    memcpy(buf, wpa_auth->addr, ETH_ALEN);
    wpa_get_ntp_timestamp(buf + ETH_ALEN);
    memcpy(buf + ETH_ALEN + 8, &group, sizeof(group));
    if (os_get_random(rkey, sizeof(rkey)) < 0)
        return -1;

    if (sha1_prf(rkey, sizeof(rkey), "Init Counter", buf, sizeof(buf),
            group->Counter, WPA_NONCE_LEN) < 0)
        return -1;
    wpa_hexdump_key(MSG_DEBUG, "Key Counter",
            group->Counter, WPA_NONCE_LEN);

    return 0;
}