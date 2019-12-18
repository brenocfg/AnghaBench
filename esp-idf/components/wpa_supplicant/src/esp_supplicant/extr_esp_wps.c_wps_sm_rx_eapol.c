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
struct wps_rx_param {int len; int /*<<< orphan*/ * sa; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int ESP_ERR_NO_MEM ; 
 int ESP_FAIL ; 
 int /*<<< orphan*/  SIG_WPS_RX ; 
 int WPS_ADDR_LEN ; 
 int /*<<< orphan*/  gWpsSm ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_free (struct wps_rx_param*) ; 
 scalar_t__ os_zalloc (int) ; 
 int wps_post (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wps_rxq_enqueue (struct wps_rx_param*) ; 
 int wps_sm_rx_eapol_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int wps_sm_rx_eapol(u8 *src_addr, u8 *buf, u32 len)
{
    if (!gWpsSm) {
        return ESP_FAIL;
    }

#ifdef USE_WPS_TASK
    {
        struct wps_rx_param *param = (struct wps_rx_param *)os_zalloc(sizeof(struct wps_rx_param));   /* free in task */

        if (!param) {
            return ESP_ERR_NO_MEM;
        }

        param->buf = (u8 *)os_zalloc(len);   /* free in task */
        if (!param->buf) {
            os_free(param);
            return ESP_ERR_NO_MEM;
        }
        memcpy(param->buf, buf, len);
        param->len = len;
        memcpy(param->sa, src_addr, WPS_ADDR_LEN);

        wps_rxq_enqueue(param);
        return wps_post(SIG_WPS_RX, 0);
    }
#else
    return wps_sm_rx_eapol_internal(src_addr, buf, len);
#endif
}