#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct esp_tls {int dummy; } ;
struct TYPE_3__ {scalar_t__ cacert_bytes; scalar_t__ cacert_buf; } ;
typedef  TYPE_1__ esp_tls_cfg_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 int ESP_TLS_ERR_SSL_WANT_READ ; 
 int ESP_TLS_ERR_SSL_WANT_WRITE ; 
 scalar_t__ REQUEST ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  WEB_URL ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  esp_tls_conn_delete (struct esp_tls*) ; 
 struct esp_tls* esp_tls_conn_http_new (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int esp_tls_conn_read (struct esp_tls*,char*,int) ; 
 int esp_tls_conn_write (struct esp_tls*,scalar_t__,size_t) ; 
 int portTICK_PERIOD_MS ; 
 int /*<<< orphan*/  putchar (char) ; 
 scalar_t__ server_root_cert_pem_end ; 
 scalar_t__ server_root_cert_pem_start ; 
 size_t strlen (scalar_t__) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

__attribute__((used)) static void https_get_task(void *pvParameters)
{
    char buf[512];
    int ret, len;

    while(1) {
        esp_tls_cfg_t cfg = {
            .cacert_buf  = server_root_cert_pem_start,
            .cacert_bytes = server_root_cert_pem_end - server_root_cert_pem_start,
        };
        
        struct esp_tls *tls = esp_tls_conn_http_new(WEB_URL, &cfg);
        
        if(tls != NULL) {
            ESP_LOGI(TAG, "Connection established...");
        } else {
            ESP_LOGE(TAG, "Connection failed...");
            goto exit;
        }
        
        size_t written_bytes = 0;
        do {
            ret = esp_tls_conn_write(tls, 
                                     REQUEST + written_bytes, 
                                     strlen(REQUEST) - written_bytes);
            if (ret >= 0) {
                ESP_LOGI(TAG, "%d bytes written", ret);
                written_bytes += ret;
            } else if (ret != ESP_TLS_ERR_SSL_WANT_READ  && ret != ESP_TLS_ERR_SSL_WANT_WRITE) {
                ESP_LOGE(TAG, "esp_tls_conn_write  returned 0x%x", ret);
                goto exit;
            }
        } while(written_bytes < strlen(REQUEST));

        ESP_LOGI(TAG, "Reading HTTP response...");

        do
        {
            len = sizeof(buf) - 1;
            bzero(buf, sizeof(buf));
            ret = esp_tls_conn_read(tls, (char *)buf, len);
            
            if(ret == ESP_TLS_ERR_SSL_WANT_WRITE  || ret == ESP_TLS_ERR_SSL_WANT_READ)
                continue;
            
            if(ret < 0)
           {
                ESP_LOGE(TAG, "esp_tls_conn_read  returned -0x%x", -ret);
                break;
            }

            if(ret == 0)
            {
                ESP_LOGI(TAG, "connection closed");
                break;
            }

            len = ret;
            ESP_LOGD(TAG, "%d bytes read", len);
            /* Print response directly to stdout as it is read */
            for(int i = 0; i < len; i++) {
                putchar(buf[i]);
            }
        } while(1);

    exit:
        esp_tls_conn_delete(tls);    
        putchar('\n'); // JSON output doesn't have a newline at end

        static int request_count;
        ESP_LOGI(TAG, "Completed %d requests", ++request_count);

        for(int countdown = 10; countdown >= 0; countdown--) {
            ESP_LOGI(TAG, "%d...", countdown);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
        ESP_LOGI(TAG, "Starting again!");
    }
}